#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <string>
#include "Types.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "ALU.h"

class ControlUnit {
private:
    Memory& memory;
    RegisterFile& registers;
    ALU& alu;

    int PC;
    uint16_t IR;
    bool halted;
    std::string errorMessage;

    byte opcode, operandR, operandX, operandY;

public:
    ControlUnit(Memory& mem, RegisterFile& reg, ALU& alu_ref);
    
    void setPC(int startAddress);
    uint16_t fetch();
    void decode(uint16_t instruction);
    bool validateInstruction();
    void execute();
    void step();
};

#endif