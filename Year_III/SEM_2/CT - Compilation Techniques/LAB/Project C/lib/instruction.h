#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "symbol.h"
#include "value.h"

enum { 
    O_ADD_C, O_ADD_D, O_ADD_I,
    O_SUB_C, O_SUB_D, O_SUB_I,
    O_MUL_C, O_MUL_D, O_MUL_I,
    O_DIV_C, O_DIV_D, O_DIV_I,
    O_NEG_C, O_NEG_D, O_NEG_I,

    O_EQ_A, O_EQ_C, O_EQ_D, O_EQ_I,
    O_NE_A, O_NE_C, O_NE_D, O_NE_I,
    O_GT_C, O_GT_D, O_GT_I,
    O_GE_C, O_GE_D, O_GE_I,
    O_LT_C, O_LT_D, O_LT_I,
    O_LE_C, O_LE_D, O_LE_I,

    O_AND_A, O_AND_C, O_AND_D, O_AND_I,
    O_OR_A, O_OR_C, O_OR_D, O_OR_I,
    O_NOT_A, O_NOT_C, O_NOT_D, O_NOT_I,

    O_JMP,
    O_JT_A, O_JT_C, O_JT_D, O_JT_I,
    O_JF_A, O_JF_C, O_JF_D, O_JF_I,

    O_CAST_C_D, O_CAST_C_I, O_CAST_D_C, O_CAST_D_I, O_CAST_I_C, O_CAST_I_D,

    O_CALL,
    O_CALLEXT,
    O_DROP,
    O_ENTER,

    O_LOAD,
    O_NOP,

    O_HALT,
    O_INSERT,

    O_OFFSET,

    O_PUSHFPADDR,
    O_PUSHCT_A, O_PUSHCT_C, O_PUSHCT_D, O_PUSHCT_I,

    O_RET,
    O_STORE
};  // all opcodes; each one starts with O_

typedef struct _Instruction {
    int opcode;  // O_*
    union {
        long int i;  // int, char
        double d;
        void *addr;
    } args[2];
    struct _Instruction *prev, *next;  // links to prev, next instructions
} Instruction;

Instruction *instructions, *lastInstruction;  // double linked list

Instruction *createInstruction(int opcode);

void insertInstructionAfter(Instruction *after, Instruction *i);

void deleteInstructionsAfter(Instruction *after);

Instruction *addInstruction(int opcode);

Instruction *addInstructionAfter(Instruction *after, int opcode);

Instruction *addInstructionA(int opcode, void *a);

Instruction *addInstructionI(int opcode, long int i);

Instruction *addInstructionII(int opcode, long int i1, long int i2);

Instruction *appendInstruction(Instruction *i);

Instruction *getRVal(RetVal *rv);

void addCastInstruction(Instruction *after, Type *actualType, Type *neededType);

Instruction *createCondJmp(RetVal *rv);

#endif