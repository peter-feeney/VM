#if !defined(REGISTERS_H)
#define REGISTERS_H

// define program's registers
// TODO: Set system so that program can do I/O operations in command line
typedef enum {
  R0, R1, R2, R3, R4 , R5, R6, SYSTEM,
  NUM_OF_REGISTERS
} Registers;

// setting register as easy as: register[A] = some_value
int registers[NUM_OF_REGISTERS];

#endif
