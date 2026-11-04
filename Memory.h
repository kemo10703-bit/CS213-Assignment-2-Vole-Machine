#ifndef MEMORY_H
#define MEMORY_H

#include "Types.h"

class Memory {
private:
    static constexpr int MEMORY_SIZE = 256;
    byte cells[MEMORY_SIZE]{};

public:
    byte read(int address) const;
    void write(int address, byte value);
    void setMemory(int address, byte value);
    bool isValidAddress(int address) const;
    void displayMemory() const;
};

#endif
