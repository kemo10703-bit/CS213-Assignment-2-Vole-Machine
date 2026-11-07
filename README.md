# Vole Machine Simulator

## Build
Compile the project with C++17:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic ALU.cpp Memory.cpp RegisterFile.cpp ControlUnit.cpp ProgramLoader.cpp DisplayState.cpp VoleMachine.cpp mainProject.cpp main.cpp -o vole
```

Run `./vole` (or `vole.exe` on Windows).

## Program input format
The program loader expects one 16-bit instruction per token, written as exactly four hexadecimal digits. Each instruction is loaded into two consecutive memory cells, most-significant byte first.

Example file: `program_example.txt`

```text
2105
2207
5312
C000
```

This example loads 05 into R1, 07 into R2, adds R1 and R2 into R3, then halts.

## Current implementation notes
- Memory contains 256 byte cells (00–FF).
- RegisterFile contains 16 registers (R0–RF).
- Program loading defaults to address 10 (hex).
- The loader validates hexadecimal instruction formatting and available memory before writing the program.
- ControlUnit implements opcodes 1 through C using the current team ALU interface.
- The simulator stops after 10,000 instructions as a safeguard against an accidental infinite loop.
- `main.cpp` is an optional Memory/RegisterFile smoke test. Define `VOLE_COMPONENT_TEST_MAIN` to build it as the entry point; the normal simulator entry point is `mainProject.cpp`.

## Before final submission
Check the exact assignment handout for the required program-file format, start address, opcode semantics, and output behavior. In particular, confirm the course's 8-bit floating-point representation used by opcode 6; the ALU implementation is retained from the team's submitted version and has not been independently validated against an instructor test set.
