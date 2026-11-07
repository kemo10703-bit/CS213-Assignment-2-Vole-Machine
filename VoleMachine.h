#ifndef VOLE_MACHINE_H
#define VOLE_MACHINE_H

#include <string>

#include "Memory.h"
#include "RegisterFile.h"
#include "ALU.h"
#include "ControlUnit.h"
#include "ProgramLoader.h"
#include "DisplayState.h"

class VoleMachine {
private:
    Memory memory;
    RegisterFile registers;
    ALU alu;
    ControlUnit controlUnit;
    ProgramLoader programLoader;
    DisplayState stateDisplay;

public:
    VoleMachine();

    void initialize();
    bool loadProgram(const std::string& fileName, int startAddress = 0x10);
    void step();
    void run();
    void displayState() const;
};

#endif
