#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include <string>
#include "Memory.h"

class ProgramLoader {
public:
    bool loadFromFile(const std::string& fileName, int startAddress, Memory& memory) const;
    bool validateProgram(const std::string& fileName, int startAddress) const;
};

#endif
