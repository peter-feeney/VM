#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "instructions.h"
#include "registers.h"
#define MAX_NUM_INSTRUCTIONS 5000
#define next_instr *instrs[idx++]


/* 
 *
 * Reads in input in binary form from another
 * file.  
 * 
 * Add string support later
 * 
 */ 
// O(log n) power function
int power(int x, int y) {
 return y ? ( y % 2 ? x : 1) * power(x * x, y >> 1) : 1;
}

// Match raw binary code to register number
int match_reg(int regCode) {
    // 7 registers so far
    // curr_pow starts at 12
    switch (regCode)
    {
    case 4096: // 0001
    case 65536:
    case 1048576:
        return R0;
        break;
    case 8192: // 0010
    case 131072:
    case 2097152:
        return R1;
        break;
    case 12288: // 0011
    case 196608:
    case 3145728:
        return R2;
        break;
    case 16384: // 0100
    case 262144:
    case 4194304:
        return R3;
        break;
    case 20480: // 0101
    case 327680:
    case 5242880:
        return R4;
        break;
    case 28672: // 0111
    case 458752:
    case 7340032:
        return R5;
        break;
    case 32768: // 1000
    case 524288:
    case 8288608:
        return R6;
        break;
    case 36864: // 1001
    case 589824:
    case 9437184:
        return SYSTEM;
        break;
    default:
        perror("Invalid register.\n");
        exit(EXIT_FAILURE);
        break;
    }
   return 0; 
}


// Need to match register numbers as well :(
// Matches raw binry information to actual instructions
int matchInstruction(int *instrs[], int instrNo, int arg1, int arg2, int arg3, int *curr_idx) {
    int idx = *curr_idx;
    switch (instrNo)
    {
    case 64: // 1) 2 ^ 6 (000 001)
        next_instr = HLT;
        break;
    case 128: // 2) 2 ^ 7 (000 010)  
        next_instr = PSH;
        next_instr = arg1;
        break;
    case 192: // 3) (2 ^ 7) + (2 ^ 6) (000 011)
        next_instr = POP;
        break;
    case 256: // 4) (2 ^ 8) (000 100)
        next_instr = SET;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 320: // 5) (2 ^ 8) + (2 ^ 6) (000 101)
        next_instr = ADD;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 384: // 6) (2 ^ 8) + (2 ^ 7) (000 110)
        next_instr = MUL;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 448: // 7) (2 ^ 8) + (2 ^ 7) + (2 ^ 6) (000 111)
        next_instr = SUB;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 512: // 8) (2 ^ 9) (001 000)
        next_instr = DIV;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 576: // 9) (2 ^ 9) + (2 ^ 6) (001 001)
        next_instr = MOD;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 640: // 10) (2 ^ 9) + (2 ^ 7) (001 010)
        next_instr = GLD;
        next_instr = arg1;
        break;
    case 704: // 11) (2 ^ 9) + (2 ^ 7) + (2 ^ 6) (001 011)
        next_instr = GPT;
        next_instr = match_reg(arg1);
        break;
    case 768: // 12) (2 ^ 9) + (2 ^ 8) (001 100)
        next_instr = AND;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 832: // 13) (2 ^ 9) + (2 ^ 8) + (2 ^ 6) (001 101)
        next_instr = OR;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 960: // 14) (2 ^ 9) + (2 ^ 8) + (2 ^ 7) + (2 ^ 6) (001 111)
        next_instr = NOT;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1024: // 15) (2 ^ 10) (010 000)
        next_instr = XOR;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        next_instr = arg3;
        break;
    case 1088: // 16) (2 ^ 10) + (2 ^ 6) (010 001)
        next_instr = BNE;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1152: // 17) (2 ^ 10) + (2 ^ 7) (010 010)
        next_instr = BLT;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1216: // 18) (2 ^ 10) + (2 ^ 7) + (2 ^ 6) (010 011)
        next_instr = BLT;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1280: // 19) (2 ^ 10) + (2 ^ 8) (010 100)
        next_instr = BGT;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1344: // 20) (2 ^ 10) + (2 ^ 8) + (2 ^ 6) (010 101)
        next_instr = BGE;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1408: // 21) (2 ^ 10) + (2 ^ 8) + (2 ^ 7) (010 110)
        next_instr = BLE;
        next_instr = match_reg(arg1);
        next_instr = match_reg(arg2);
        next_instr = arg3;
        break;
    case 1472: // 22) (2 ^ 10) + (2 ^ 8) + (2 ^ 7) + (2 ^ 6) (010 111)
        next_instr = BEQZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break; 
    case 1536: // 23) (2 ^ 10) + (2 ^ 9) (011 000)
        next_instr = BGEZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1600: // 24) (2 ^ 10) + (2 ^ 9) + (2 ^ 6) (011 001)
        next_instr = BNEZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1664: // 25) (2 ^ 10) + (2 ^ 9) + (2 ^ 7) (011 010)
        next_instr = BLEZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1728: // 25) (2 ^ 10) + (2 ^ 9) + (2 ^ 7) + (2 ^ 6) (011 011)
        next_instr = BLTZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1792: // 26) (2 ^ 10) + (2 ^ 9) + (2 ^ 8) (011 100)
        next_instr = BGTZ;
        next_instr = match_reg(arg1);
        next_instr = arg2;
        break;
    case 1856: // 27) (2 ^ 10) + (2 ^ 9) + (2 ^ 8) + (2 ^ 6) (011 101)
        next_instr = JMP;
        break;
    case 1920: // 28) (2 ^ 10) + (2 ^ 9) + (2 ^ 8) + (2 ^ 7) (011 110)
        next_instr = SYSCALL;
        break;
    default:
        perror("Invalid instruction number.\n");
        exit(EXIT_FAILURE);
        break;
    }
    curr_idx = &idx;
    return 1;
}


int readBinaryLine(char input[], int *instructions[], int *curr_idx) {
        unsigned int bit_mask = 1 << 31;
        int curr_pow = 0;
        int instrNo = 0;
        int arg1, arg2, arg3;
        arg1 = arg2 = arg3 = __INT_MAX__;
        int i;
        // 14 digits of waste (can use for other things later)
        for(i = 0; i < 14; i++) {
            bit_mask >>= 1;
        }
        // Get instruction number (capacity for 64 instructions)
        for(i = 14; i < 20; i++) {
            curr_pow = 6;
            if(bit_mask & (unsigned char)input[i]) {
                instrNo += power(2, curr_pow++);
            }
            bit_mask >>= 1;
        }
        // Get arguments for instruction
        // Up to 16 registers are possible, and instructions can have up to 3 arguments
        for(i = 20; i < 24; i++) {
            if(bit_mask & (unsigned char)input[i]) {
                if(arg1 == __INT_MAX__) {
                    arg1 = 0;
                }
                arg1 += power(2, curr_pow++);
            }
            bit_mask >>= 1;
        }

        for(i = 24; i < 28; i++) {
            if(bit_mask & (unsigned char)input[i]) {
                if(arg2 == __INT_MAX__) {
                    arg2 = 0;
                }
                arg2 += power(2, curr_pow++);
            }
            bit_mask >>= 1;
        }

        for(i = 28; i < 32; i++) {
            if(bit_mask & (unsigned char)input[i]) {
                if(arg3 == __INT_MAX__) {
                    arg3 = 0;
                }
                arg3 += power(2, curr_pow++);                
            }
            bit_mask >>= 1;
        }
        // Match number to actual instruction
        matchInstruction(instructions, instrNo, arg1, arg2, arg3, curr_idx);
        return 1;
}


int readInInstructions(int *instructions[]) {
    FILE *fp;
    int curr_idx;
    char binaryIndicator; 
    bool isBinary;
    char filename[255]; // max size of Linux filename is 255 characters
    char bin_string[32];

    printf("What is the name of the file to be read?\n");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Are the instructions in binary format? (y/n)");
    scanf(" %c", &binaryIndicator); // need space to avoid newline from last scanf to be turned into input

    if(binaryIndicator != 'y' && binaryIndicator != 'n') {
        perror("Invalid character\n");
        exit(EXIT_FAILURE);
    } 

    isBinary = binaryIndicator == 'y';

    if(isBinary) {
        printf("%s%s%s\n", "We are dealing with file ", filename, " in binary format.");
        curr_idx = 0;
        while(fgets(bin_string, 32, fp)) {
            readBinaryLine(bin_string, instructions, &curr_idx);
        }
        return 1;
    } else {
        perror("String input not handled yet\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp);
}


