#include <iostream>
#include <limits>
#include <string>

#include "VoleMachine.h"

int main() {
    VoleMachine machine;

    std::cout << "========================================\n";
    std::cout << "       VOLE MACHINE SIMULATOR\n";
    std::cout << "========================================\n";

    std::string fileName;
    std::cout << "Enter program file name: ";
    std::cin >> fileName;

    int startAddress = 0x10;
    std::cout << "Start address (hex, default 10): ";
    std::string addressText;
    std::cin >> addressText;

    try {
        startAddress = static_cast<int>(std::stoul(addressText, nullptr, 16));
    } catch (...) {
        std::cerr << "Invalid address. Using default address 10.\n";
        startAddress = 0x10;
    }

    if (!machine.loadProgram(fileName, startAddress)) {
        return 1;
    }

    int choice = 0;
    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Run program\n";
        std::cout << "2. Execute one instruction\n";
        std::cout << "3. Display machine state\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                machine.run();
                break;
            case 2:
                machine.step();
                machine.displayState();
                break;
            case 3:
                machine.displayState();
                break;
            case 4:
                std::cout << "Exiting simulator.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
