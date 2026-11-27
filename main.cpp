#include <iostream>
#include <string>
#include "Airline.h"

const std::string FLIGHT_FILE = "flights_test2.txt";
const std::string PASSENGER_FILE = "passengers_test2.txt";

int main_menu();

int main(){

    std::cout << "Version: 1.0"
        "\nTerm Project - Flight Management Program in C++"
        "\nProduced By: Sam Katevatis, Mahmood Muntasir and Elijah Black Kettle"
        "\nYear: 2026"
        "\n\n<<< Press ENTER to continue >>>"
    << std::endl;

    std::cin.get();

    Airline airline("ENSF 337 Airlines");
    if (!airline.loadData(FLIGHT_FILE, PASSENGER_FILE)) {
        return 1;
    }

    Flight* selected = nullptr;
    int choice = -1;

    while (choice != 0) {
        choice = main_menu();

        if (choice == 1) {
            airline.displayFlights();
        }
        else if (choice == 2) {
            std::string code;
            std::cout << "Enter flight code: ";
            std::cin >> code;

            selected = airline.findFlight(code);
            if (selected == nullptr) {
                std::cout << "Flight not found." << std::endl;
            } else {
                std::cout << "Selected flight " << code << "." << std::endl;
            }
        }
        else if (choice >= 3 && choice <= 6 && selected == nullptr) {
            std::cout << "Please select a flight first (option 2)." << std::endl;
        }
        else if (choice == 3) {
            selected->displaySeatMap();
        }
        else if (choice == 4) {
            selected->displayPassengers();
        }
        else if (choice == 5) {
            int id, row;
            std::string first, last, phone;
            char seat;

            std::cout << "Enter passenger ID: ";
            std::cin >> id;
            std::cout << "Enter first name: ";
            std::cin >> first;
            std::cout << "Enter last name: ";
            std::cin >> last;
            std::cout << "Enter phone number: ";
            std::cin >> phone;
            std::cout << "Enter seat row: ";
            std::cin >> row;
            std::cout << "Enter seat letter: ";
            std::cin >> seat;

            selected->addPassenger(Passenger(id, first, last, phone, row, seat));
            std::cout << "Passenger added." << std::endl;
        }
        else if (choice == 6) {
            int id;
            std::cout << "Enter passenger ID to remove: ";
            std::cin >> id;

            selected->removePassenger(id);
            std::cout << "Passenger removed." << std::endl;
        }
        else if (choice == 7) {
            if (airline.savePassengerData(PASSENGER_FILE)) {
                std::cout << "Data saved." << std::endl;
            }
        }
        else if (choice != 0) {
            std::cout << "Invalid choice." << std::endl;
        }
    }

    std::cout << "Goodbye." << std::endl;
    return 0;
}

int main_menu(){
    std::cout << "\nPlease select one of the following options:"
        "\n\n\t1. Display all flights"
        "\n\t2. Select a flight"
        "\n\t3. Display selected flight seat map"
        "\n\t4. Display passengers' information"
        "\n\t5. Add a new passenger"
        "\n\t6. Remove an existing passenger"
        "\n\t7. Save data"
        "\n\t0. Quit"
    << std::endl;

    int choice;
    if (!(std::cin >> choice)) {
        return 0;
    }
    return choice;
}
