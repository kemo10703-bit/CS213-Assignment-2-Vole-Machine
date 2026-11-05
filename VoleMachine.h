#pragma once
#include<string>
#include "Memory.h"
#include "RegisterFile.h"
#include "ALU.h"
#include "ControlUnit.h"
#include "ProgramLoader.h"
class VoleMachine
{
private:
	Memory memory;
	RegisterFile registers;
	ALU alu;
	ControlUnit controlUnit;
public:
	VoleMachine();


	void loadProgram(string fileName);
	void runAtOnce();
	void stepByStep();
	void displayState();

};

