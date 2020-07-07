# VM

### What
Simple virtual machine written in C that emulates a MIPS-like assembly language on a fictional CPU.

### Why
I created this primarily as a way to have fun with C, and to reacquaint myself with some assembly and elementary systems programming concepts. This repository is a space where I can mess around with things in C that interest me if I want to do so.

There were various points during the making of this project where I had to choose between writing maintable code or using some cool feature of C. I chose the latter option every time. So if you're a potential employer and you're reading this then I want you to know that I would never create monstrosities like the macros in eval.c on the job.

### How

The VM takes in instructions encoded in binary and spits out the output of those instructions.

Supported instructions include:
  
  - PSH [arg1]: Push argument onto stack.
  - ADD [reg_number] [arg1] [arg2]: Store arg1 + arg2 in Reg[reg_number] 
  - POP: Pop argument from stack.
  - SET [reg_number] [arg1]: Set reg_number to value arg1.
  - DIV [reg_number] [arg1] [arg2]: Store arg1 / arg2 in Reg[reg_number]
  - MUL [reg_number] [arg1] [arg2]: Store arg1 * arg2 in Reg[reg_number]
  - SUB [reg_number] [arg1] [arg2]: Store arg1 - arg2 in Reg[reg_number]
  - GLD [reg_number]: Load value from reg_number to the stack.
  - GPT [reg_number]: Push top of stack onto Reg[reg_number]
  - AND [reg_number] [arg1] [arg2]: Store arg1 & arg2 in Reg[reg_number]
  - MOD [reg_number] [arg1] [arg2]: Store arg1 % arg2 in Reg[reg_number]
  - OR [reg_number] [arg1] [arg2]: Store arg1 | arg2 in Reg[reg_number]
  - NOT [reg_number] [arg1]: Store ~arg1 in Reg[reg_number]
  - XOR [reg_number] [arg1] [arg2]: Store arg1 ^ arg2 in Reg[reg_number]
  - BEQ [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 == arg2
  - BNE [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 != arg2
  - BLT [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 < arg2
  - BGT [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 > arg2
  - BEQZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 == 0
  - BGE [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 >= arg2
  - BLE [arg1] [arg2] [arg3]: Branch to location specified by arg3 if arg1 <= arg2
  - BLTZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 < 0
  - BGEZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 >= 0
  - BNEZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 != 0
  - BLEZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 <= 0 
  - BGTZ [arg1] [arg2]: Branch to location specified by arg2 if arg1 > 0
  - JMP [arg1]: Go to location specified by arg1.
  - SYSCALL [arg1]: Scan in number into Reg[arg1] if Reg[SYSTEM] == 1, otherwise print out whatever is in Reg[arg1]
  - HLT: Stop program from running. (Needed at the end of any input)
  
  When you start the program it'll ask you for the name of a file. Enter in the name of a properly encoded text file -- it must be in binary for now, but I'll work on adding in support for string input later on.
  
  What makes a properly encoded text file? Read the source code of IO.c and do a little bit of reverse engineering and you'll be able to figure it out. Again, this project is exploratory in nature and practical usage wasn't really a prime consideration here.
  
  Feel free to send all questions, comments, suggestions for improvement, hate mail, love letters, job offers (!), etc. to pfeeney@terpmail.umd.edu.
