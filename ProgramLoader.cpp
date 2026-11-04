#include "ProgramLoader.h"
#include <fstream>
#include<iostream>
using namespace std;
ProgramLoader::ProgramLoader(string path)
{
	filePath = path;
}

bool ProgramLoader::validateInstruction(string line)
{
	if (line.length() != 4)
	{
		return false;
	}
	return true;

}

bool ProgramLoader::loadProgram(Memory& memory)
{
	ifstream file(filePath);

	if(!file.is_open())
	{
		cerr << "Error : could not open file" << filePath << endl;
		return false;
	}

	string instruction;
	int address = 0x10;

	while (file >> instruction)
	{
		if (validateInstruction(instruction))
		{
			//memory.write(address,instructionL)  لما كلاس تجهز هلغي كومنت
			address++;
		}
		else
		{
			cerr << "Error : Invalid instruction -> "<<instruction << endl;
			file.close();
			return false;
		}
	}

	file.close();
	return true;



}


