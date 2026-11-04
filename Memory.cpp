#include "Memory.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

bool Memory::isValidAddress(int address) const {
    return address >= 0 && address < MEMORY_SIZE;
}

byte Memory::read(int address) const {
    if (!isValidAddress(address)) {
        throw std::out_of_range("Memory address must be between 0 and 255.");
    }

    return cells[address];
}

void Memory::write(int address, byte value) {
    if (!isValidAddress(address)) {
        throw std::out_of_range("Memory address must be between 0 and 255.");
    }

    if (address == 0xFF) {
        std::cout << static_cast<char>(value);
        return;
    }

    cells[address] = value;
}

void Memory::setMemory(int address, byte value) {
    if (!isValidAddress(address)) {
        throw std::out_of_range("Memory address must be between 0 and 255.");
    }

    // Directly initializes/updates memory without triggering screen output.
    cells[address] = value;
}

void Memory::displayMemory() const {
    std::cout << std::uppercase << std::hex << std::setfill('0');

    for (int address = 0; address < MEMORY_SIZE; ++address) {
        if (address % 16 == 0) {
            std::cout << "\n" << std::setw(2) << address << ": ";
        }

        std::cout << std::setw(2)
                  << static_cast<unsigned int>(cells[address]) << ' ';
    }

    std::cout << std::dec << std::setfill(' ') << '\n';
}
