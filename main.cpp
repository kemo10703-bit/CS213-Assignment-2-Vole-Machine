// Optional component smoke test. Compile with -DVOLE_COMPONENT_TEST_MAIN
// to use this test entry point instead of mainProject.cpp.
#ifdef VOLE_COMPONENT_TEST_MAIN
#include <iostream>
#include "Memory.h"
#include "RegisterFile.h"

int main() {
    Memory memory;
    RegisterFile registers;

    memory.setMemory(10, 25);
    memory.setMemory(20, 50);
    std::cout << "Memory[10] = " << static_cast<int>(memory.read(10)) << '\n';
    std::cout << "Memory[20] = " << static_cast<int>(memory.read(20)) << '\n';

    registers.setRegister(1, 100);
    registers.setRegister(2, 200);
    std::cout << "R1 = " << static_cast<int>(registers.getRegister(1)) << '\n';
    std::cout << "R2 = " << static_cast<int>(registers.getRegister(2)) << '\n';
    registers.displayRegisters();
    return 0;
}
#endif
