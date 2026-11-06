#include "DisplayState.h"
#include <iostream>

using namespace std;

void DisplayState::displayState(
    const RegisterFile& reg,
    const Memory& mem) const {

    cout << "\n===== Vole Machine State =====\n";

    cout << "\nRegisters:\n";
    reg.displayRegisters();

    cout << "\nMemory:\n";
    mem.displayMemory();

    cout << "\n==============================\n";
}