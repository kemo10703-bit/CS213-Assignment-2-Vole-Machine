#pragma once
#include<string>
#include<Memory.h>
using namespace std;
class ProgramLoader
{
private:
	string filePath;
public:
	ProgramLoader(string Path);

	bool loadProgram(Memory& memory);
	bool validateInstruction(string line);


};

