#ifndef ALU_H
#define ALU_H

#include "Types.h"

class ALU {
public:
    byte addInteger(byte a, byte b);
    byte addFloat(byte a, byte b);

    byte bitwiseOR(byte a, byte b);
    byte bitwiseAND(byte a, byte b);
    byte bitwiseXOR(byte a, byte b);

    byte rotate(byte value, int count);
};

#endif