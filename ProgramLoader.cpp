#include "ProgramLoader.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {
bool parseInstruction(const std::string& token, byte& highByte, byte& lowByte) {
    if (token.size() != 4) return false;
    for (char ch : token) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) return false;
    }

    const unsigned int value = static_cast<unsigned int>(std::stoul(token, nullptr, 16));
    highByte = static_cast<byte>((value >> 8) & 0xFF);
    lowByte = static_cast<byte>(value & 0xFF);
    return true;
}

bool readAndValidate(const std::string& fileName, int startAddress, std::vector<byte>& bytes) {
    if (startAddress < 0 || startAddress > 0xFE) {
        std::cerr << "Invalid start address. Use a value from 00 to FE.\n";
        return false;
    }

    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Could not open program file: " << fileName << '\n';
        return false;
    }

    std::string token;
    while (file >> token) {
        byte highByte = 0;
        byte lowByte = 0;
        if (!parseInstruction(token, highByte, lowByte)) {
            std::cerr << "Invalid instruction '" << token
                      << "'. Each instruction must contain four hexadecimal digits.\n";
            return false;
        }

        bytes.push_back(highByte);
        bytes.push_back(lowByte);
        if (startAddress + static_cast<int>(bytes.size()) > 256) {
            std::cerr << "Program is too large for memory at the selected start address.\n";
            return false;
        }
    }

    if (file.bad()) {
        std::cerr << "An error occurred while reading the program file.\n";
        return false;
    }
    if (bytes.empty()) {
        std::cerr << "Program file is empty.\n";
        return false;
    }
    return true;
}
}

bool ProgramLoader::validateProgram(const std::string& fileName, int startAddress) const {
    std::vector<byte> bytes;
    return readAndValidate(fileName, startAddress, bytes);
}

bool ProgramLoader::loadFromFile(const std::string& fileName, int startAddress, Memory& memory) const {
    std::vector<byte> bytes;
    if (!readAndValidate(fileName, startAddress, bytes)) return false;

    for (std::size_t i = 0; i < bytes.size(); ++i) {
        memory.setMemory(startAddress + static_cast<int>(i), bytes[i]);
    }
    return true;
}
