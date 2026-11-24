// main.cpp
// Frontend for the Flight Management Application System (FMAS).
// Handles the title screen, menus and user input. All flight and
// passenger data is managed by the Airline, Flight and Passenger classes.

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

// ---------- Main ----------

int main() {
    displayTitle();

    // Load all flights and passengers from the data files.
    Airline airline("FMAS");
    if (!airline.loadData(FLIGHT_FILE, PASSENGER_FILE)) {
        cout << "Unable to load data. Program terminated.\n";
        return 1;
    }

    int choice = 0;
    while (choice != 8) {
        choice = showMenu();
        cout << endl;

        switch (choice) {
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
