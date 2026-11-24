#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <vector>
#include "Flight.h"

class Airline {
private:
    std::string name;
    std::vector<Flight> flights;

public:
    Airline(std::string airline_name);

    void displayFlights() const;
    Flight* findFlight(const std::string& flight_code);

    bool loadData(const std::string& flight_file,
                  const std::string& passenger_file);

    bool savePassengerData(const std::string& passenger_file);
};

#endif