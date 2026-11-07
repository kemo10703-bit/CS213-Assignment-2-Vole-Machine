#include "VoleMachine.h"

#include <iostream>
#include <stdexcept>

VoleMachine::VoleMachine()
    : memory(), registers(), alu(), controlUnit(memory, registers, alu),
      programLoader(), startAddress(0x10) {
    initialize();
}

void VoleMachine::initialize() {
    memory = Memory{};
    registers = RegisterFile{};
    startAddress = 0x10;
    controlUnit.setPC(startAddress);
}

bool VoleMachine::loadProgram(const std::string& fileName, int programStartAddress) {
    if (!programLoader.loadFromFile(fileName, programStartAddress, memory)) {
        std::cerr << "Failed to load program.\n";
        return false;
    }

    startAddress = programStartAddress;
    controlUnit.setPC(startAddress);
    std::cout << "Program loaded successfully at address 0x"
              << std::hex << startAddress << std::dec << ".\n";
    return true;
}

void VoleMachine::step() {
    if (controlUnit.isHalted()) {
        std::cout << "Machine is halted. No more instructions to execute.\n";
        return;
    }

    try {
        controlUnit.step();
    } catch (const std::exception& error) {
        std::cerr << "Execution error: " << error.what() << '\n';
    }
}

void VoleMachine::run() {
    constexpr int MAX_INSTRUCTIONS = 10000;
    int executed = 0;

    while (!controlUnit.isHalted() && executed < MAX_INSTRUCTIONS) {
        try {
            controlUnit.step();
        } catch (const std::exception& error) {
            std::cerr << "Execution error: " << error.what() << '\n';
            return;
        }
        ++executed;
    }

    if (!controlUnit.isHalted()) {
        std::cerr << "Execution stopped after " << MAX_INSTRUCTIONS
                  << " instructions to prevent an infinite loop.\n";
    } else {
        std::cout << "Program halted after " << executed << " instruction(s).\n";
    }
}

void VoleMachine::displayState() const {
    std::cout << "\n========== VOLE MACHINE STATE ==========\n";
    std::cout << "PC: 0x" << std::hex << controlUnit.getPC() << std::dec << '\n';
    std::cout << "Halted: " << (controlUnit.isHalted() ? "Yes" : "No") << '\n';

    std::cout << "\n---------- REGISTERS ----------\n";
    registers.displayRegisters();

    std::cout << "\n---------- MEMORY ----------\n";
    memory.displayMemory();
    std::cout << "========================================\n";
}
