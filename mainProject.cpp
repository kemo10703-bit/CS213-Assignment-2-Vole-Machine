#include <iostream>
#include <string>
#include "VoleMachine.h"
using namespace std;
int main()
{
    cout << "<========================================>" << endl;
    cout << "     WELCOME TO VOLE MACHINE SIMULATOR  " << endl;
    cout << "<========================================>" << endl;
    VoleMachine machine;

    string filename;
    cout << "Enter the program file name (e.g., program.txt) : ";
    cin >> filename;

    machine.loadProgram(filename);

    int choice;
    do {
        cout << "\n--- CHOOSE EXECUTION MODE ---" << endl;
        cout << "1. Run Program at Once" << endl;
        cout << "2. Run Step by Step" << endl;
        cout << "3. Display Machine State" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            machine.runAtOnce();
            break;
        case 2:
            machine.stepByStep();
            break;
        case 3:
            machine.displayState();
            break;
        case 4:
            cout << "Exiting simulator. Good bye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}



