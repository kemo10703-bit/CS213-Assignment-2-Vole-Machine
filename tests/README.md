# Vole Machine Test Programs

Twenty separate input programs for checking the simulator. Each instruction is exactly four hexadecimal digits; load and run each file separately. The current application loads programs at address 10 (hex) by default.

## Test list and expected results

| File | What it checks | Expected result from current source |
|---|---|---|
| program_01_load_immediate.txt | Load immediate | R1 = 05; halted |
| program_02_two_registers.txt | Load two registers | R1 = 05, R2 = 07; halted |
| program_03_integer_addition.txt | Integer addition | R3 = 0C; halted |
| program_04_store_to_memory.txt | Store register in memory | Memory[0A] = 0A; halted |
| program_05_move_register.txt | Move R1 to R2 | R1 = 0A, R2 = 0A; halted |
| program_06_bitwise_or.txt | OR | R3 = 0F; halted |
| program_07_bitwise_and.txt | AND | R3 = 01; halted |
| program_08_bitwise_xor.txt | XOR | R3 = 0E; halted |
| program_09_rotate_right.txt | Rotate right by one bit | R1 = C0; halted |
| program_10_load_zeroed_memory.txt | Read untouched memory | R1 = 00; halted |
| program_11_store_then_load.txt | Store and reload | R2 = 0B; Memory[20] = 0B; halted |
| program_12_addition_overflow.txt | 8-bit addition wraparound | R3 = 00; halted |
| program_13_branch_not_taken.txt | Conditional branch not taken | R2 = 22; halted |
| program_14_branch_taken.txt | Conditional branch taken | Branch to address 16; halt |
| program_15_multiple_memory_cells.txt | Store/read two memory cells | R2 = 0C, R3 = 0D; Memory[20] = 0C, Memory[21] = 0D; halted |
| program_16_float_addition_provisional.txt | Floating-point addition | R3 = 50 with the current ALU implementation; confirm the course's required float format |
| program_17_add_and_move_chain.txt | Addition followed by move | R3 = 07, R4 = 07 after MOVE; halted |
| program_18_bitwise_chain.txt | OR followed by AND | R3 = F0; halted |
| program_19_zero_register_branch.txt | Branch when R1 equals R0 | Branch to address 16; R2 remains 00; halt |
| program_20_combined_operations.txt | Addition, OR, then rotate | R3 = 8F after rotate; R1 = 0F; halted |

## How to run
1. Build the complete simulator using the project build command.
2. Launch it and enter one filename from this folder when prompted.
3. Select Run, then Display State.
4. Compare the actual state with the expected result above.
5. Capture evidence only after that test has actually run and passed.

## Important status
These are prepared test inputs and expected outcomes inferred from the current repository implementation. **They have not yet been executed against the complete project build.** Do not report them as passed and do not create screenshots claiming success until they are run. The floating-point test is provisional until the assignment handout's 8-bit floating-point representation is confirmed. Also verify the handout's required input format, start address, opcode behavior, and output requirements before submission.
