#include "Passenger.h"
#include <iostream>

Passenger::Passenger(int id, std::string first, std::string last,
                     std::string phone, int row, char seat)
    : passenger_id(id), first_name(first), last_name(last),
      phone_number(phone), seat_row(row), seat_letter(seat) {
}

int Passenger::getPassengerId() const {
    return passenger_id;
}

std::string Passenger::getFirstName() const {
    return first_name;
}

std::string Passenger::getLastName() const {
    return last_name;
}

std::string Passenger::getPhoneNumber() const {
    return phone_number;
}

int Passenger::getSeatRow() const {
    return seat_row;
}

char Passenger::getSeatLetter() const {
    return seat_letter;
}

void Passenger::print() const {
    std::cout << passenger_id << " "
              << first_name << " "
              << last_name << " "
              << phone_number << " "
              << seat_row << " "
              << seat_letter << std::endl;
}