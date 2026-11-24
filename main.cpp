// main.cpp
// Frontend for the Flight Management Application System (FMAS).
// Handles the title screen, menus and user input. All flight and
// passenger data is managed by the Airline, Flight and Passenger classes.

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include "Airline.h"

using namespace std;

// Data files. To use the second input set, change only these two names.
const string FLIGHT_FILE = "flights.txt";
const string PASSENGER_FILE = "passengers.txt";

// ---------- Input helpers ----------

// Waits for the user to press Return.
void pressReturn() {
    cout << "\n<<< Press Return to Continue>>>>";
    string line;
    getline(cin, line);
}

// Prompts until the user enters a whole number. Discards the rest of the line.
int readInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        if (cin.eof())   // input ended (e.g. Ctrl+D), stop instead of looping
            exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Prompts for a single word (no spaces). Discards the rest of the line.
string readWord(const string& prompt) {
    string word;
    cout << prompt;
    cin >> word;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return word;
}

// ---------- Screens ----------

// Title screen shown when the program starts.
void displayTitle() {
    cout << "Version: 1.0"
         << "\nTerm Project - Flight Management Program in C++"
         << "\nProduced by: Sam Katevatis, Mahmood Muntasir and Elijah Black Kettle"
         << "\nYear: 2026\n";
    pressReturn();
}

// Prints the main menu and returns the user's choice.
int showMenu() {
    cout << "\nPlease select one of the following options:\n"
         << "\n   1. Display all flights."
         << "\n   2. Select a flight."
         << "\n   3. Display Flight Seat Map."
         << "\n   4. Display Passengers Information."
         << "\n   5. Add a New Passenger."
         << "\n   6. Remove an Existing Passenger."
         << "\n   7. Save data."
         << "\n   8. Quit.\n\n";
    return readInt("Enter your choice: (1, 2, 3, 4, 5, 6, 7, or 8) ");
}

// ---------- Menu actions ----------

// Option 2: asks for a flight and returns it, or nullptr if not found.
// BACKEND NOTE: The sample run selects a flight by its list number (e.g. 1),
// but Airline only offers findFlight(code). Adding something like
// getFlightCount() and getFlight(int index) to Airline would allow that.
Flight* selectFlight(Airline& airline) {
    string code = readWord("Enter the flight code: ");
    Flight* flight = airline.findFlight(code);

    if (flight == nullptr)
        cout << "No flight with code " << code << " was found.\n";
    else
        cout << "You have selected flight " << flight->getFlightCode()
             << " from " << flight->getOrigin()
             << " to " << flight->getDestination() << ".\n";
    return flight;
}

// Option 4: prints the passenger table for a flight.
// BACKEND NOTE: Passenger::print() separates fields with single spaces, so
// rows do not line up under these column headers. Using setw in print()
// would fix the alignment.
void showPassengers(const Flight& flight) {
    const string line(61, '-');
    cout << "Passenger List (Flight: " << flight.getFlightCode()
         << " from " << flight.getOrigin()
         << " to " << flight.getDestination() << ")\n\n"
         << "ID      First Name   Last Name    Phone           Row   Seat\n"
         << line << "\n";
    flight.displayPassengers();
    cout << line << "\n";
}

// Option 5: reads a new passenger's details and adds them to the flight.
// BACKEND NOTE: Flight::addPassenger() does no checking and returns void,
// so the checks below are done here. Ideally addPassenger() would validate
// and return a bool. IDs are only checked within this flight because
// Airline has no way to look through every flight's passengers.
void addPassenger(Flight& flight) {
    int id = readInt("Please enter the passenger id: ");
    string first = readWord("Please enter the passenger first name: ");
    string last = readWord("Please enter the passenger last name: ");
    string phone = readWord("Please enter the passenger phone number: ");
    int row = readInt("Enter the passenger's desired row: ");
    char seat = toupper(readWord("Enter the passenger's desired seat: ")[0]);

    // Seat must exist on this aircraft (rows start at 1, seats start at 'A').
    char last_seat = 'A' + flight.getSeatsPerRow() - 1;
    if (row < 1 || row > flight.getNumberOfRows() || seat < 'A' || seat > last_seat) {
        cout << "Seat " << row << seat << " does not exist on this flight.\n";
        return;
    }

    // ID and seat must not already be used on this flight.
    for (const Passenger& p : flight.getPassengers()) {
        if (p.getPassengerId() == id) {
            cout << "Passenger id " << id << " is already on this flight.\n";
            return;
        }
        if (p.getSeatRow() == row && p.getSeatLetter() == seat) {
            cout << "Seat " << row << seat << " is already taken.\n";
            return;
        }
    }

    flight.addPassenger(Passenger(id, first, last, phone, row, seat));
    cout << "Passenger " << first << " " << last
         << " was added to flight " << flight.getFlightCode() << ".\n";
}

// Option 6: removes a passenger from the flight by id.
// BACKEND NOTE: Flight::removePassenger() returns void, so the passenger is
// looked up here first to confirm they exist and to get their name.
void removePassenger(Flight& flight) {
    int id = readInt("Please enter the id of the passenger that needs to be removed: ");

    for (const Passenger& p : flight.getPassengers()) {
        if (p.getPassengerId() == id) {
            // Copy the name before removing, since p is erased with it.
            string name = p.getFirstName() + " " + p.getLastName();
            flight.removePassenger(id);
            cout << "\nPassenger " << name << " was successfully removed from flight "
                 << flight.getFlightCode() << ".\n";
            return;
        }
    }
    cout << "\nNo passenger with id " << id << " is on this flight.\n";
}

// Option 7: asks for confirmation, then saves all passengers to the file.
void saveData(Airline& airline) {
    string answer = readWord("Save the updated passenger data to " + PASSENGER_FILE + "? (Y or N) ");

    if (toupper(answer[0]) != 'Y')
        cout << "\nData was not saved.\n";
    else if (airline.savePassengerData(PASSENGER_FILE))
        cout << "\nAll passenger data was saved successfully.\n";
    else
        cout << "\nPassenger data could not be saved.\n";
}

// ---------- Main ----------

int main() {
    displayTitle();

    // Load all flights and passengers from the data files.
    Airline airline("FMAS");
    if (!airline.loadData(FLIGHT_FILE, PASSENGER_FILE)) {
        cout << "Unable to load data. Program terminated.\n";
        return 1;
    }

    Flight* selected = nullptr;   // currently selected flight (none at start)
    int choice = 0;

    while (choice != 8) {
        choice = showMenu();
        cout << endl;

        switch (choice) {
            case 1:
                // BACKEND NOTE: displayFlights() does not number the flights
                // or show rows / seats per row like the sample run does.
                airline.displayFlights();
                pressReturn();
                break;
            case 2: {
                // Keep the previous selection if the code is not found.
                Flight* found = selectFlight(airline);
                if (found != nullptr)
                    selected = found;
                pressReturn();
                break;
            }
            case 3:
            case 4:
            case 5:
            case 6:
                // Options 3 to 6 all need a selected flight.
                if (selected == nullptr)
                    cout << "Please select a flight first (option 2).\n";
                else if (choice == 3)
                    // BACKEND NOTE: displaySeatMap() is missing the
                    // "A B C D" column letters shown in the sample run.
                    selected->displaySeatMap();
                else if (choice == 4)
                    showPassengers(*selected);
                else if (choice == 5)
                    addPassenger(*selected);
                else
                    removePassenger(*selected);
                pressReturn();
                break;
            case 7:
                saveData(airline);
                pressReturn();
                break;
            case 8:
                cout << "Program terminated.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 8.\n";
                pressReturn();
        }
    }

    return 0;
}
