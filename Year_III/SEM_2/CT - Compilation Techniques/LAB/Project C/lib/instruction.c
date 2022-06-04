#include "instruction.h"

#include <stdlib.h>

#include "domain_analyzer.h"
#include "stdio.h"
#include "token.h"
#include "virtual_machine.h"

Instruction *createInstruction(int opcode) {
    Instruction *instruction;
    SAFE_ALLOC(instruction, Instruction)
    instruction->opcode = opcode;

    return instruction;
}

void insertInstructionAfter(Instruction *after, Instruction *instruction) {
    instruction->next = after->next;
    instruction->prev = after;
    after->next = instruction;

    if (instruction->next == NULL) {
        lastInstruction = instruction;
    }
}
    
void deleteInstructionsAfter(Instruction *instruction) {
    // for (Instruction *i = instruction->next; i != NULL; i = i->next) {
    //     free(i);
    // }
    instruction->next = NULL;
    lastInstruction = instruction;
}

Instruction *addInstruction(int opcode) {
    Instruction *instruction = createInstruction(opcode);
    instruction->next = NULL;
    instruction->prev = lastInstruction;

    if (lastInstruction) {
        lastInstruction->next = instruction;
    } else {
        instructions = instruction;
    }

    lastInstruction = instruction;

    return instruction;
}

Instruction *addInstructionAfter(Instruction *after, int opcode) {
    Instruction *instruction = createInstruction(opcode);

    insertInstructionAfter(after, instruction);

    return instruction;
}

Instruction *addInstructionA(int opcode, void *a) {
    Instruction *instruction = addInstruction(opcode);
    instruction->args[0].addr = a;

    return instruction;
}

Instruction *addInstructionI(int opcode, long int i) {
    Instruction *instruction = addInstruction(opcode);
    instruction->args[0].i = i;

    return instruction;
}

Instruction *addInstructionII(int opcode, long int i1, long int i2) {
    Instruction *instruction = addInstruction(opcode);
    instruction->args[0].i = i1;
    instruction->args[1].i = i2;

    return instruction;
}

Instruction *appendInstruction(Instruction *instruction) {
    lastInstruction->next = instruction;
    instruction->prev = lastInstruction;
    lastInstruction = instruction;

    return instruction;
}

Instruction *getRVal(RetVal *rv) {
    if (rv->isLVal) {
        switch (rv->type.typeBase) {
            case TB_INT:
            case TB_DOUBLE:
            case TB_CHAR:
            case TB_STRUCT:
                addInstructionI(O_LOAD, typeArgSize(&rv->type));
                break;
            default:
                tokenError(current_token, "unhandled type: %d", rv->type.typeBase);
        }
    }
    return lastInstruction;
}

void addCastInstruction(Instruction *after, Type *actualType, Type *neededType) {
    if (actualType->nElements >= 0 || neededType->nElements >= 0) return;

    switch (actualType->typeBase) {
        case TB_CHAR:
            switch (neededType->typeBase) {
                case TB_CHAR:
                    break;
                case TB_INT:
                    addInstructionAfter(after, O_CAST_C_I);
                    break;
                case TB_DOUBLE:
                    addInstructionAfter(after, O_CAST_C_D);
                    break;
            }
            break;
        case TB_INT:
            switch (neededType->typeBase) {
                case TB_CHAR:
                    addInstructionAfter(after, O_CAST_I_C);
                    break;
                case TB_INT:
                    break;
                case TB_DOUBLE:
                    addInstructionAfter(after, O_CAST_I_D);
                    break;
            }
            break;
        case TB_DOUBLE:
            switch (neededType->typeBase) {
                case TB_CHAR:
                    addInstructionAfter(after, O_CAST_D_C);
                    break;
                case TB_INT:
                    addInstructionAfter(after, O_CAST_D_I);
                    break;
                case TB_DOUBLE:
                    break;
            }
            break;
    }
}

Instruction *createCondJmp(RetVal *rv) {
    if (rv->type.nElements >= 0) {  // arrays
        return addInstruction(O_JF_A);
    } 
    // non-arrays
    getRVal(rv);
    switch (rv->type.typeBase) {
        case TB_CHAR:
            return addInstruction(O_JF_C);
        case TB_DOUBLE:
            return addInstruction(O_JF_D);
        case TB_INT:
            return addInstruction(O_JF_I);
        default:
            return NULL;
    }
}