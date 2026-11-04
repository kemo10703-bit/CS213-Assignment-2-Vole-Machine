#include <iostream>
#include "Memory.h"
#include "RegisterFile.h"

using namespace std;

int main() {

    Memory memory;
    RegisterFile registers;

    memory.setMemory(10, 25);
    memory.setMemory(20, 50);

    cout << "Memory[10] = " << (int)memory.read(10) << endl;
    cout << "Memory[20] = " << (int)memory.read(20) << endl;

    registers.setRegister(1, 100);
    registers.setRegister(2, 200);

    cout << "R1 = " << (int)registers.getRegister(1) << endl;
    cout << "R2 = " << (int)registers.getRegister(2) << endl;

    cout << "\n";
    registers.displayRegisters();

    
    return 0;
}