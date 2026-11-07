#include "ControlUnit.h"

#include <stdexcept>

ControlUnit::ControlUnit(Memory& mem, RegisterFile& reg, ALU& alu_ref)
    : memory(mem), registers(reg), alu(alu_ref), PC(0), IR(0), halted(false),
      errorMessage(), opcode(0), operandR(0), operandX(0), operandY(0) {}

void ControlUnit::setPC(int startAddress) {
    if (startAddress < 0 || startAddress > 0xFE) {
        throw std::out_of_range("Program counter must be between 00 and FE.");
    }
    PC = startAddress;
    halted = false;
    errorMessage.clear();
}

std::uint16_t ControlUnit::fetch() {
    if (!memory.isValidAddress(PC) || !memory.isValidAddress(PC + 1)) {
        throw std::out_of_range("Program counter is outside executable memory.");
    }

    IR = static_cast<std::uint16_t>(
        (static_cast<std::uint16_t>(memory.read(PC)) << 8) |
        static_cast<std::uint16_t>(memory.read(PC + 1)));
    PC += 2;
    return IR;
}

void ControlUnit::decode(std::uint16_t instruction) {
    opcode = static_cast<byte>((instruction >> 12) & 0x0F);
    operandR = static_cast<byte>((instruction >> 8) & 0x0F);
    operandX = static_cast<byte>((instruction >> 4) & 0x0F);
    operandY = static_cast<byte>(instruction & 0x0F);
}

bool ControlUnit::validateInstruction() {
    if (opcode < 1 || opcode > 0xC) {
        errorMessage = "Invalid opcode. Supported opcodes are 1 through C.";
        return false;
    }
    if (opcode == 4 && operandR != 0) {
        errorMessage = "Invalid MOVE format. Expected 4 0 R S.";
        return false;
    }
    if (opcode == 0xA && operandX != 0) {
        errorMessage = "Invalid ROTATE format. Expected A R 0 X.";
        return false;
    }
    if (opcode == 0xC && (operandR != 0 || operandX != 0 || operandY != 0)) {
        errorMessage = "Invalid HALT format. Expected C000.";
        return false;
    }
    return true;
}

void ControlUnit::execute() {
    const int address = (static_cast<int>(operandX) << 4) | operandY;

    switch (opcode) {
        case 0x1:
            registers.setRegister(operandR, memory.read(address));
            break;
        case 0x2:
            registers.setRegister(operandR, static_cast<byte>(address));
            break;
        case 0x3:
            memory.write(address, registers.getRegister(operandR));
            break;
        case 0x4:
            registers.setRegister(operandY, registers.getRegister(operandX));
            break;
        case 0x5:
            registers.setRegister(operandR,
                alu.addInteger(registers.getRegister(operandX), registers.getRegister(operandY)));
            break;
        case 0x6:
            registers.setRegister(operandR,
                alu.addFloat(registers.getRegister(operandX), registers.getRegister(operandY)));
            break;
        case 0x7:
            registers.setRegister(operandR,
                alu.bitwiseOR(registers.getRegister(operandX), registers.getRegister(operandY)));
            break;
        case 0x8:
            registers.setRegister(operandR,
                alu.bitwiseAND(registers.getRegister(operandX), registers.getRegister(operandY)));
            break;
        case 0x9:
            registers.setRegister(operandR,
                alu.bitwiseXOR(registers.getRegister(operandX), registers.getRegister(operandY)));
            break;
        case 0xA:
            registers.setRegister(operandR,
                alu.rotate(registers.getRegister(operandR), operandY));
            break;
        case 0xB:
            if (registers.getRegister(operandR) == registers.getRegister(0)) {
                if (address > 0xFE) {
                    throw std::out_of_range("Jump target must be between 00 and FE.");
                }
                PC = address;
            }
            break;
        case 0xC:
            halted = true;
            break;
        default:
            throw std::runtime_error("Unsupported instruction.");
    }
}

void ControlUnit::step() {
    if (halted) return;

    try {
        const std::uint16_t instruction = fetch();
        decode(instruction);
        if (!validateInstruction()) {
            throw std::runtime_error(errorMessage);
        }
        execute();
    } catch (const std::exception& error) {
        halted = true;
        errorMessage = error.what();
        throw;
    }
}

int ControlUnit::getPC() const { return PC; }
bool ControlUnit::isHalted() const { return halted; }
const std::string& ControlUnit::getErrorMessage() const { return errorMessage; }
