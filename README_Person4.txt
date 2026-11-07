PERSON 4 - COMPLETED IMPLEMENTATION

Files:
- ProgramLoader.h / ProgramLoader.cpp
- VoleMachine.h / VoleMachine.cpp
- mainProject.cpp
- Updated ControlUnit.h / ControlUnit.cpp (integration fixes)

Build from the project folder:
g++ -std=c++17 -Wall -Wextra -pedantic Memory.cpp RegisterFile.cpp ALU.cpp ControlUnit.cpp ProgramLoader.cpp VoleMachine.cpp mainProject.cpp -o vole

Run:
./vole
On Windows:
.\vole.exe

Program file format:
Each instruction is exactly four hexadecimal characters, one instruction per token/line.
Example:
2105
2207
5312
C000

The loader stores each 16-bit instruction as two bytes (big-endian) and advances memory by two addresses.
Default start address is hexadecimal 10.

IMPORTANT INTEGRATION NOTES:
1. This code uses the actual ALU names found in the repository:
   bitwiseOR, bitwiseAND, bitwiseXOR, rotate.
2. ControlUnit has been updated with isHalted() and getPC() so VoleMachine can control execution and display PC.
3. The existing project Memory::write(FF, value) prints a character. ProgramLoader uses setMemory() so loading program bytes does not accidentally print.
4. The current UML/brief described opcodes 1 through C. Opcode D is not implemented because it is not in the supplied team interface.
5. The 10,000-instruction run limit prevents a broken infinite loop from locking the simulator. Adjust only if your instructor specifies another behavior.
6. Before final submission, compare the program file format and default start address with the instructor's exact assignment sheet.
