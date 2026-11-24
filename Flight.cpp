#include "Flight.h"
#include <iostream>

Flight::Flight(std::string code, std::string orig, std::string dest,
               int rows, int seats)
    : flight_code(code), origin(orig), destination(dest),
      number_of_rows(rows), seats_per_row(seats) {
}

void Flight::displaySeatMap() const {
    std::vector<std::vector<char>> seat_map(
        number_of_rows, std::vector<char>(seats_per_row, '-'));

    for (const Passenger& passenger : passengers) {
        int row_index = passenger.getSeatRow() - 1;
        int seat_index = passenger.getSeatLetter() - 'A';

        if (row_index >= 0 && row_index < number_of_rows &&
            seat_index >= 0 && seat_index < seats_per_row) {

            seat_map[row_index][seat_index] = 'X';
        }
    }

    std::cout << "\nSeat Map for " << flight_code << "\n";

    for (int row = 0; row < number_of_rows; row++) {
        std::cout << row + 1 << "  ";

        for (int seat = 0; seat < seats_per_row; seat++) {
            std::cout << seat_map[row][seat] << " ";
        }

        std::cout << std::endl;
    }
}

void Flight::displayPassengers() const {
    for (const Passenger& passenger : passengers) {
        passenger.print();
    }
}

void Flight::addPassenger(const Passenger& passenger) {
    passengers.push_back(passenger);
}

void Flight::removePassenger(int passenger_id) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if (it->getPassengerId() == passenger_id) {
            passengers.erase(it);
            return;
        }
    }
}

std::string Flight::getFlightCode() const {
    return flight_code;
}

std::string Flight::getOrigin() const {
    return origin;
}

std::string Flight::getDestination() const {
    return destination;
}

int Flight::getNumberOfRows() const {
    return number_of_rows;
}

int Flight::getSeatsPerRow() const {
    return seats_per_row;
}

const std::vector<Passenger>& Flight::getPassengers() const {
    return passengers;
}
