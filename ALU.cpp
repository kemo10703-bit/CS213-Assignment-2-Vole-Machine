#include "ALU.h"

// Integer Addition
byte ALU::addInteger(byte a, byte b) {
    return a + b;
}

// Bitwise OR
byte ALU::bitwiseOR(byte a, byte b) {
    return a | b;
}

// Bitwise AND
byte ALU::bitwiseAND(byte a, byte b) {
    return a & b;
}

// Bitwise XOR
byte ALU::bitwiseXOR(byte a, byte b) {
    return a ^ b;
}

// Rotate Right
byte ALU::rotate(byte value, int count) {

    count = count % 8;

    if (count < 0)
        count += 8;

    if (count == 0)
        return value;

    return (value >> count) | (value << (8 - count));
}

// Floating Point Addition
byte ALU::addFloat(byte a, byte b) {

    if (a == 0)
        return b;

    if (b == 0)
        return a;

    int signA = (a >> 7) & 1;
    int expA = (a >> 4) & 7;
    int mantA = a & 0x0F;

    int signB = (b >> 7) & 1;
    int expB = (b >> 4) & 7;
    int mantB = b & 0x0F;

    int realExpA = expA - 4;
    int realExpB = expB - 4;

    int fullMantA = 16 + mantA;
    int fullMantB = 16 + mantB;

    if (realExpA > realExpB) {

        int diff = realExpA - realExpB;

        if (diff >= 5)
            fullMantB = 0;
        else
            fullMantB >>= diff;

        realExpB = realExpA;
    }
    else if (realExpB > realExpA) {

        int diff = realExpB - realExpA;

        if (diff >= 5)
            fullMantA = 0;
        else
            fullMantA >>= diff;

        realExpA = realExpB;
    }

    int signedA = (signA == 1) ? -fullMantA : fullMantA;
    int signedB = (signB == 1) ? -fullMantB : fullMantB;

    int sum = signedA + signedB;

    int resultSign = 0;

    if (sum < 0) {
        resultSign = 1;
        sum = -sum;
    }

    if (sum == 0)
        return 0;

    int resultExp = realExpA;

    if (sum >= 32) {
        sum >>= 1;
        resultExp++;
    }
    else {
        while (sum < 16 && resultExp > -4) {
            sum <<= 1;
            resultExp--;
        }
    }

    if (resultExp > 3) {
        resultExp = 3;
        sum = 31;
    }

    if (resultExp < -4)
        return 0;

    int finalExp = resultExp + 4;
    byte finalMant = sum & 0x0F;

    return (resultSign << 7) | (finalExp << 4) | finalMant;
}