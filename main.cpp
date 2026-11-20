#include <iostream>

void main_menu();

int main(){

    std::cout << "Version: 1.0"
        "\nTerm Project - Flight Management Program in C++"
        "\nProduced By: Sam Katevatis, Mahmood Muntasir and Elijah Black Kettle"
        "\nYear: 2026"
        "\n\n<<< Press ENTER to continue >>>"
    << std::endl;

    std::cin.get();
    main_menu();

    return 0;
}

void main_menu(){
    std::cout << "Please select one of the following options:"
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
    std::cin >> choice;
}
