#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
private:
    int passenger_id;
    std::string first_name;
    std::string last_name;
    std::string phone_number;
    int seat_row;
    char seat_letter;

public:
    Passenger(int id, std::string first, std::string last,
              std::string phone, int row, char seat);

    int getPassengerId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
    int getSeatRow() const;
    char getSeatLetter() const;

    void print() const;
};

#endif