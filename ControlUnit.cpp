#include "ControlUnit.h"

#include <stdexcept>

ControlUnit::ControlUnit(Memory& mem, RegisterFile& reg, ALU& alu_ref)
    : memory(mem), registers(reg), alu(alu_ref), PC(0), IR(0), halted(false),
      errorMessage(), opcode(0), operandR(0), operandX(0), operandY(0) {}

void ControlUnit::setPC(int startAddress) {
    if (!memory.isValidAddress(startAddress) || startAddress == 0xFF) {
        throw std::out_of_range("Program counter start address must be between 00 and FE.");
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
        static_cast<std::uint16_t>(memory.read(PC + 1))
    );
    PC += 2;
    return IR;
}

void ControlUnit::decode(std::uint16_t instruction) {
    opcode   = static_cast<byte>((instruction >> 12) & 0x0F);
    operandR = static_cast<byte>((instruction >> 8) & 0x0F);
    operandX = static_cast<byte>((instruction >> 4) & 0x0F);
    operandY = static_cast<byte>(instruction & 0x0F);
}

bool ControlUnit::validateInstruction() {
    if (opcode >= 1 && opcode <= 12) {
        if (opcode == 4 && operandR != 0) {
            errorMessage = "MOVE instruction must have 0 in its second nibble.";
            return false;
        }
        if (opcode == 12 && (operandR != 0 || operandX != 0 || operandY != 0)) {
            errorMessage = "HALT instruction must be C000.";
            return false;
        }
        if (opcode == 10 && operandX != 0) {
            errorMessage = "ROTATE instruction must use format A R 0 X.";
            return false;
        }
        return true;
    }

    errorMessage = "Invalid opcode.";
    return false;
}

void ControlUnit::execute() {
    const int address = (static_cast<int>(operandX) << 4) | operandY;

    switch (opcode) {
        case 1:
            registers.setRegister(operandR, memory.read(address));
            break;
        case 2:
            registers.setRegister(operandR, static_cast<byte>(address));
            break;
        case 3:
            memory.write(address, registers.getRegister(operandR));
            break;
        case 4:
            registers.setRegister(operandY, registers.getRegister(operandX));
            break;
        case 5:
            registers.setRegister(operandR,
                alu.addInteger(registers.getRegister(operandX),
                               registers.getRegister(operandY)));
            break;
        case 6:
            registers.setRegister(operandR,
                alu.addFloat(registers.getRegister(operandX),
                             registers.getRegister(operandY)));
            break;
        case 7:
            registers.setRegister(operandR,
                alu.bitwiseOR(registers.getRegister(operandX),
                              registers.getRegister(operandY)));
            break;
        case 8:
            registers.setRegister(operandR,
                alu.bitwiseAND(registers.getRegister(operandX),
                               registers.getRegister(operandY)));
            break;
        case 9:
            registers.setRegister(operandR,
                alu.bitwiseXOR(registers.getRegister(operandX),
                               registers.getRegister(operandY)));
            break;
        case 10:
            registers.setRegister(operandR,
                alu.rotate(registers.getRegister(operandR), operandY));
            break;
        case 11:
            if (registers.getRegister(operandR) == registers.getRegister(0)) {
                PC = address;
            }
            break;
        case 12:
            halted = true;
            break;
        default:
            halted = true;
            errorMessage = "Unsupported instruction.";
            break;
    }
}

void ControlUnit::step() {
    if (halted) {
        return;
    }

    const std::uint16_t instruction = fetch();
    decode(instruction);

    if (!validateInstruction()) {
        halted = true;
        throw std::runtime_error(errorMessage);
    }

    execute();
}

int ControlUnit::getPC() const {
    return PC;
}

bool ControlUnit::isHalted() const {
    return halted;
}

const std::string& ControlUnit::getErrorMessage() const {
    return errorMessage;
}
