#ifndef VM_H
#define VM_H

#include "instruction.h"

#define STACK_SIZE (32 * 1024)
#define GLOBAL_SIZE (32*1024)

char stack[STACK_SIZE];
char *SP, *FP, *IP;
char *stack_end;

char globals[GLOBAL_SIZE];
int numGlobals;

void *allocGlobal(int size);

void put_i();

void get_i();

void put_d();

void get_d();

void put_s();

void get_s();

void put_c();

void get_c();

void seconds();

void run_vm(Instruction *IP);

void printInstructions(Instruction *IP);

void printInstruction(Instruction *instruction);

#endif