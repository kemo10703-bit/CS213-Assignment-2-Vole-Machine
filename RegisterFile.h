#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "Types.h"

class RegisterFile {
private:
    static constexpr int REGISTER_COUNT = 16;
    byte registers[REGISTER_COUNT]{};

public:
    byte getRegister(int index) const;
    void setRegister(int index, byte value);
    void displayRegisters() const;
};

#endif
