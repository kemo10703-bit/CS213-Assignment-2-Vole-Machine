#include "ControlUnit.h"

ControlUnit::ControlUnit(Memory& mem, RegisterFile& reg, ALU& alu_ref)
    : memory(mem), registers(reg), alu(alu_ref), PC(0), IR(0), halted(false) {}

void ControlUnit::setPC(int startAddress) {
    PC = startAddress;
    halted = false;
}

uint16_t ControlUnit::fetch() {
    IR = (memory.read(PC) << 8) | memory.read(PC + 1);
    PC += 2;
    return IR;
}

void ControlUnit::decode(uint16_t instruction) {
    opcode   = (instruction & 0xF000) >> 12;
    operandR = (instruction & 0x0F00) >> 8;
    operandX = (instruction & 0x00F0) >> 4;
    operandY = (instruction & 0x000F);
}

bool ControlUnit::validateInstruction() {
    if (opcode >= 1 && opcode <= 12) return true;
    errorMessage = "Invalid Instruction!";
    return false;
}

void ControlUnit::execute() {
    byte regX = registers.getRegister(operandX);
    byte regY = registers.getRegister(operandY);
    int address = (operandX << 4) | operandY;

    switch (opcode) {
        case 1: registers.setRegister(operandR, memory.read(address)); break;
        case 2: registers.setRegister(operandR, address); break;
        case 3: memory.write(address, registers.getRegister(operandR)); break;
        case 4: registers.setRegister(operandY, regX); break;
        case 5: registers.setRegister(operandR, alu.addInteger(regX, regY)); break;
        case 6: registers.setRegister(operandR, alu.addFloat(regX, regY)); break;
        case 7: registers.setRegister(operandR, alu.bitwiseOr(regX, regY)); break;
        case 8: registers.setRegister(operandR, alu.bitwiseAnd(regX, regY)); break;
        case 9: registers.setRegister(operandR, alu.bitwiseXor(regX, regY)); break;
        case 0xA: registers.setRegister(operandR, alu.rotateRight(registers.getRegister(operandR), operandY)); break;
        case 0xB: if (registers.getRegister(operandR) == registers.getRegister(0)) PC = address; break;
        case 0xC: halted = true; break;
    }
}

void ControlUnit::step() {
    if (halted) return;
    uint16_t inst = fetch();
    decode(inst);
    if (validateInstruction()) execute();
    else halted = true;
}