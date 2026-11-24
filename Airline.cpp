#include "Airline.h"
#include "FileRecordIO.h"
#include <iostream>

Airline::Airline(std::string airline_name)
    : name(airline_name) {
}

bool Airline::loadData(const std::string& flight_file,
                       const std::string& passenger_file) {

    std::vector<FlightRecord> flight_records;
    std::string error_message;

    if (!readFlightRecords(flight_file, flight_records, error_message)) {
        std::cerr << error_message << std::endl;
        return false;
    }

    flights.clear();

    for (const FlightRecord& record : flight_records) {
        flights.push_back(
            Flight(record.flight_code,
                   record.origin,
                   record.destination,
                   record.number_of_rows,
                   record.seats_per_row)
        );
    }

    std::vector<PassengerRecord> passenger_records;

    if (!readPassengerRecords(passenger_file,
                              passenger_records,
                              error_message)) {
        std::cerr << error_message << std::endl;
        return false;
    }

    for (const PassengerRecord& record : passenger_records) {
        for (Flight& flight : flights) {
            if (flight.getFlightCode() == record.flight_code) {
                flight.addPassenger(
                    Passenger(record.passenger_id,
                             record.first_name,
                             record.last_name,
                             record.phone_number,
                             record.seat_row,
                             record.seat_letter)
                );

                break;
            }
        }
    }

    return true;
}

void Airline::displayFlights() const {
    std::cout << "\nAvailable Flights:\n";

    for (const Flight& flight : flights) {
        std::cout << flight.getFlightCode() << " | "
                  << flight.getOrigin() << " -> "
                  << flight.getDestination() << std::endl;
    }
}

Flight* Airline::findFlight(const std::string& flight_code) {
    for (Flight& flight : flights) {
        if (flight.getFlightCode() == flight_code) {
            return &flight;
        }
    }

    return nullptr;
}

bool Airline::savePassengerData(const std::string& passenger_file) {
    std::vector<PassengerRecord> passenger_records;
    std::string error_message;

    for (const Flight& flight : flights) {
        for (const Passenger& passenger : flight.getPassengers()) {
            PassengerRecord record;

            record.flight_code = flight.getFlightCode();
            record.passenger_id = passenger.getPassengerId();
            record.first_name = passenger.getFirstName();
            record.last_name = passenger.getLastName();
            record.phone_number = passenger.getPhoneNumber();
            record.seat_row = passenger.getSeatRow();
            record.seat_letter = passenger.getSeatLetter();

            passenger_records.push_back(record);
        }
    }

    if (!writePassengerRecords(passenger_file,
                               passenger_records,
                               error_message)) {
        std::cerr << error_message << std::endl;
        return false;
    }

    return true;
}