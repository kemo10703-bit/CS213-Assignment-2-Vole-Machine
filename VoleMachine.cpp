#include "VoleMachine.h"
#include<iostream>

using namespace std;

VoleMachine::VoleMachine()
{

}

void VoleMachine::loadProgram(string fileName)
{
	ProgramLoader loader(fileName);
	if (loader.loadProgram(memory))
	{
		cout << "Program loaded Successfully into vole Machine memory!" << endl;

	}
	else
	{
		cerr << "Failed to load the program." << endl;
	}

}

void VoleMachine::runAtOnce()
{
	cout << "Running the program at once..." << endl;
}

void VoleMachine::stepByStep()
{
	cout << "Executing step by step..." << endl;
}

void VoleMachine::displayState()
{
	cout << "---- Vole Machine State ----" << endl;
}
