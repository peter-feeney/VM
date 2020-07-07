#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "eval.h"
#include "registers.h"
#include "instructions.h"
#include "IO.h"
#define MAX_NUM_INSTRUCTIONS 5000

// "instruction pointer" --> index of current argument being executed
int ip = 0;
// "last argument" --> furthest point where program executed
int last_arg = 0;
// "stack pointer" --> index that points to last element in the stack
// initalized at -1 to indicate that stack is empty.
int sp = -1;

// store stack as an array (for now)
int stack[256];

// "running" --> indicates whether or not program has reached halt instruction
bool running = true;
bool is_jmp = false;

/*
 * Test program defined below [Instruction
 * set stored as array]
 * Program should push 5 and 6 to the stack
 * ,add them and then pop the value.
 * then halt the program.
 * 
const int program[] = {
    SET, SYSTEM, 1, SYSCALL, R1,
    SET, SYSTEM, 0, SYSCALL, R1,  
    HLT
};
 */
int *program[MAX_NUM_INSTRUCTIONS];

// fetch the current instruction
int fetch() {
  return *program[ip];
}

int main() {
  readInInstructions(program);
  // Program runs until halt instruction reached
  while (running)
  {
    eval(fetch());
    last_arg++;
    is_jmp ? is_jmp = false : ip++;
    }

    // automatically exits with code 0
}
