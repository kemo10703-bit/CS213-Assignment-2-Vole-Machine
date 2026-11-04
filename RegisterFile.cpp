#include "RegisterFile.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

byte RegisterFile::getRegister(int index) const {
    if (index < 0 || index >= REGISTER_COUNT) {
        throw std::out_of_range("Register index must be between 0 and 15.");
    }

    return registers[index];
}

void RegisterFile::setRegister(int index, byte value) {
    if (index < 0 || index >= REGISTER_COUNT) {
        throw std::out_of_range("Register index must be between 0 and 15.");
    }

    registers[index] = value;
}

void RegisterFile::displayRegisters() const {
    std::cout << std::uppercase << std::hex << std::setfill('0');

    for (int i = 0; i < REGISTER_COUNT; ++i) {
        std::cout << 'R' << std::hex << i << ": "
                  << std::setw(2)
                  << static_cast<unsigned int>(registers[i]);

        if (i % 4 == 3) {
            std::cout << '\n';
        } else {
            std::cout << "    ";
        }
    }

    std::cout << std::dec << std::setfill(' ');
}
