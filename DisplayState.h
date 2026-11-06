#ifndef DISPLAY_STATE_H
#define DISPLAY_STATE_H

#include "RegisterFile.h"
#include "Memory.h"

class DisplayState {
public:
    void displayState(const RegisterFile& reg,
        const Memory& mem) const;
};

#endif