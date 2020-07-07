#if !defined(INSTRUCTIONSET_H)
#define INSTRUCTIONSET_H
// define instruction set for program
typedef enum {
  PSH, ADD, POP, SET, DIV,
  MUL, SUB, GLD, GPT, AND,
  MOD, OR, NOT, XOR,
  BEQ, BNE, BLT, BGT, BEQZ,
  BGE, BLE, BLTZ, BGEZ, BNEZ,
  BLEZ, BGTZ, JMP, SYSCALL, HLT
} InstructionSet;


#endif

