#if !defined(IO_H)
#define IO_H

int power(int x, int y);
int match_reg(int regCode);
int matchInstruction(int *instructions[], int instrNo, int arg1, int arg2, int arg3, int *curr_idx);
int readBinaryLine(char input[], int *instructions[], int *curr_idx);
int readInInstructions(int* instructions[]);

#endif