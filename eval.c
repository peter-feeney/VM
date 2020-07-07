#define NEXT_ARG ((last_arg++), (*program[++ip]))
#define JUMP int location = (NEXT_ARG); ip = (location); is_jmp = true;


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include "registers.h"
#include "instructions.h"

// IDEA: Input in hex numbers translated to instructions

/*
 *  Huge switch statement below
 *  evaluates different expressions.
 *  (Most efficent way to handle this)
 */


extern int ip, sp, last_arg;
extern int stack[256];
extern bool running, is_jmp;
extern int *program[];

// Initalize integers to next three arguments
 void initalize(int *first, int *second, int *third) {
  *first = NEXT_ARG;
   if(second != NULL) *second = NEXT_ARG;
   if(third != NULL) *third = NEXT_ARG;
 }

 void eval(int instr) {

   switch(instr) {
     // end of program
     case HLT: {
        running = false;
        break;
      }
      case PSH: {
        // allocate space in stack, and then push the argument after
        // PSH instruction to the stack
        stack[++sp] = NEXT_ARG;
        break;
      }
      case POP: {
        // pop element from stack and print it out
        printf("popped %d\n", stack[sp--]);
        break;
      }
      case SET: {
        // set register to number
        int reg_number = NEXT_ARG;
        registers[reg_number] = NEXT_ARG;
        break;
      }
      case ADD: {
        // add arguments as follows: Register_To_Store_Sum, Arg1, Arg2
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg + second_arg;
        break;
      }
      case MUL: {
        // multiply arguments as follows: Register_To_Store_Prod, Arg1, Arg2
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg * second_arg;
        break;
      }
      case SUB: {
        // subtract arguments as follows: Register_To_Store_Diff, Arg1, Arg2
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg - second_arg;
        break;
      }
      case DIV: {
        // divide arguments as follows: Register_To_Store_Quot, Arg1, Arg2
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg / second_arg;
        break;
      }
      case MOD: {
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg % second_arg;
        break;
      }
      case GLD: {
        // load value from register to the stack
        stack[++sp] = registers[ NEXT_ARG ];
        break;
      }
      case GPT: {
        // Push top of stack to register.
         registers[ NEXT_ARG ] = stack[sp--];
         break;
      }
      case AND: {
        // Logical AND operation (same format as specified above)
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg & second_arg;
        break;
      }
      case OR: {
        // Logical OR operation (same format as specified above)
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg | second_arg;
        break;
      }
      case NOT: {
        // Logical NOT operation
        int reg_number = NEXT_ARG;
        registers[reg_number] = ~NEXT_ARG;
        break;
      }
      case XOR: {
        // Logical OR operation (same format as specified above)
        int reg_number, first_arg, second_arg;
        initalize(&reg_number, &first_arg, &second_arg);
        registers[reg_number] = first_arg ^ second_arg;
        break;
      }
      // arguments passed as so: Reg_1, Reg_2, Location
      case BEQ: {
        // Branch if equal to each other
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 == arg2) {JUMP};
        break;
      }
      case BNE: {
        // Branch if not equal to  each other
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 != arg2) {JUMP};
        break;
      }
      case BLT: {
        // Branch if arg1 < arg2
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 < arg2) {JUMP};
        break;
      }
      case BGT: {
        // Branch if arg1 > arg2
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 > arg2) {JUMP};
        break;
      }
      case BGE: {
        // Branch if arg1 >= arg2
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 >= arg2) {JUMP};
        break;
      }
      case BLE: {
        // Branch if arg1 <= arg2
        int arg1, arg2;
        initalize(&arg1, &arg2, NULL);
        if(arg1 <= arg2) {JUMP};
        break;
      }
      case BEQZ: {
        // Branch if arg1 == 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg == 0) {JUMP};
        break;
      }
      case BGEZ: {
        // Branch if arg1 >= 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg >= 0) {JUMP};
        break;
      }
      case BNEZ: {
        // Branch if arg1 != 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg != 0) {JUMP};
        break;
      }
      case BLEZ: {
        // Branch if arg1 <= 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg <= 0) {JUMP};
        break;
      }
      case BLTZ: {
        // Branch if arg1 <= 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg < 0) {JUMP};
        break;
      }
      case BGTZ: {
        // Branch if arg1 >= 0
        int arg;
        initalize(&arg, NULL, NULL);
        if(arg > 0) {JUMP};
        break;
      }
      case JMP: {
        JUMP;
        break;
      }
      case SYSCALL: {
        // If SYSTEM code is 1, take in input and store in register. Else output register
        int num = registers[NEXT_ARG];
        registers[SYSTEM] ? scanf("%d", &num) : printf("%d\n", num);
        break;
      }
      default:
        perror("bad instruction\n");
        exit(EXIT_FAILURE);
        break;
   }
 }
