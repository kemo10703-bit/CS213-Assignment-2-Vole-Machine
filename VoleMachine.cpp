#include "VoleMachine.h"

#include <iostream>
#include <stdexcept>

VoleMachine::VoleMachine()
    : memory(), registers(), alu(), controlUnit(memory, registers, alu),
      programLoader(), stateDisplay() {
    initialize();
}

void VoleMachine::initialize() {
    memory = Memory{};
    registers = RegisterFile{};
    controlUnit.setPC(0x10);
}

bool VoleMachine::loadProgram(const std::string& fileName, int startAddress) {
    initialize();
    if (!programLoader.loadFromFile(fileName, startAddress, memory)) {
        std::cerr << "Program loading failed.\n";
        return false;
    }

    controlUnit.setPC(startAddress);
    std::cout << "Program loaded successfully at address 0x"
              << std::hex << startAddress << std::dec << ".\n";
    return true;
}

void VoleMachine::step() {
    if (controlUnit.isHalted()) {
        std::cout << "Machine is halted. No instruction was executed.\n";
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

    if (controlUnit.isHalted() && controlUnit.getErrorMessage().empty()) {
        std::cout << "Program halted after " << executed << " instruction(s).\n";
    } else if (!controlUnit.isHalted()) {
        std::cerr << "Execution stopped after reaching the safety limit of "
                  << MAX_INSTRUCTIONS << " instructions.\n";
    }
}

void VoleMachine::displayState() const {
    std::cout << "\nPC: 0x" << std::uppercase << std::hex
              << controlUnit.getPC() << std::dec << '\n';
    std::cout << "Halted: " << (controlUnit.isHalted() ? "Yes" : "No") << '\n';
    if (!controlUnit.getErrorMessage().empty()) {
        std::cout << "Last error: " << controlUnit.getErrorMessage() << '\n';
    }
    stateDisplay.displayState(registers, memory);
}
