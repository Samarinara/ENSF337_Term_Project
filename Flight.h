#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>
#include "Passenger.h"

class Flight {
private:
    std::string flight_code;
    std::string origin;
    std::string destination;
    int number_of_rows;
    int seats_per_row;
    std::vector<Passenger> passengers;

public:
    Flight(std::string code, std::string orig, std::string dest,
           int rows, int seats);

    void displaySeatMap() const;
    void displayPassengers() const;
    void addPassenger(const Passenger& passenger);
    void removePassenger(int passenger_id);
    std::string getFlightCode() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    int getNumberOfRows() const;
    int getSeatsPerRow() const;
    const std::vector<Passenger>& getPassengers() const;
};

#endif