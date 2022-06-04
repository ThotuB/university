#define PRNT 0

#include "domain_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "instruction.h"
#include "virtual_machine.h"

Token *consumed_token;
Token *current_token;
int offset, size_args;
Instruction *current_loop;

int consumeToken(int type) {
    if (current_token->type == type) {
        consumed_token = current_token;
        current_token = current_token->next;
        // printf("consumed token: ");
        // printToken(consumed_token);

        return true;
    }
    // printf("X expected token: %s\n", token_type_name[type]);
    return false;
}

void addVar(Token *token, Type *type) {
    Symbol *symbol;
    if (current_struct) {
        if (findSymbol(&current_struct->members, token->str))
            tokenError(current_token, "symbol redefinition: %s", token->str);

        symbol = addSymbol(&current_struct->members, token->str, CLS_VAR);
    } else if (current_func) {
        symbol = findSymbol(&symbols, token->str);
        if (symbol && symbol->depth == current_depth)
            tokenError(current_token, "symbol redefinition: %s", token->str);

        symbol = addSymbol(&symbols, token->str, CLS_VAR);
        symbol->mem = MEM_LOCAL;
    } else {
        if (findSymbol(&symbols, token->str))
            tokenError(current_token, "symbol redefinition: %s", token->str);

        symbol = addSymbol(&symbols, token->str, CLS_VAR);
        symbol->mem = MEM_GLOBAL;
    }
    symbol->type = *type;

    if (current_struct || current_func) {
        symbol->offset = offset;
    } else {
        symbol->address = allocGlobal(typeFullSize(&symbol->type));
    }
    offset += typeFullSize(&symbol->type);
}

bool apply(bool (*func)(void)) {
    Token *aux_current_token = current_token;
    Token *aux_consumed_token = consumed_token;
    Instruction *aux_current_instr = lastInstruction;

    if (!func()) {
        current_token = aux_current_token;
        consumed_token = aux_consumed_token;

        deleteInstructionsAfter(aux_current_instr);

        return false;
    }

    return true;
}

/// RULES
// PROTOTYPES
bool ruleCode();
bool ruleStatementList();
bool ruleStatementElse();
bool ruleStatementIf();
bool ruleStatementWhile();
bool ruleStatementFor();
bool ruleStatementBreak();
bool ruleStatementReturn();
bool ruleStatementExpression();
bool ruleStatement();
bool ruleType();
bool ruleTypeName();
bool ruleArgumentLinstr_stmt();
bool ruleExpression();
bool ruleExpressionAssign();
bool ruleExpressionOr();
bool ruleExpressionAnd();
bool ruleExpressionEquality();
bool ruleExpressionRelational();
bool ruleExpressionAddSub();
bool ruleExpressionMulDiv();
bool ruleExpressionCast();
bool ruleExpressionUnary();
bool ruleExpressionPostfix();
bool ruleExpressionPrimary();
bool ruleArray();
bool ruleDeclareVar();
bool ruleDeclareStruct();
bool ruleFuncParam();
bool ruleFuncParams();
bool ruleDeclareFunc();

#pragma region types
bool ruleType(Type *type) {
    if (PRNT) printf("RULE TYPE\n");
    if (consumeToken(INT)) {
        type->typeBase = TB_INT;
        return true;
    }
    if (consumeToken(DOUBLE)) {
        type->typeBase = TB_DOUBLE;
        return true;
    }
    if (consumeToken(CHAR)) {
        type->typeBase = TB_CHAR;
        return true;
    }
    if (consumeToken(STRUCT)) {
        if (!consumeToken(ID)) return false;
        Token *token = consumed_token;

        Symbol *symbol = findSymbol(&symbols, token->str);
        if (symbol == NULL)
            tokenError(current_token, "undefined symbol: %s", token->str);
        if (symbol->cls != CLS_STRUCT)
            tokenError(current_token, "%s instr_stm ! a struct", token->str);

        type->typeBase = TB_STRUCT;
        type->s = symbol;

        return true;
    }

    return false;
}

bool ruleTypeName(Type *type) {
    if (PRNT) printf("RULE TYPE NAME\n");
    if (!ruleType(type)) return false;
    if (ruleArray(type)) {
    } else {
        type->nElements = -1;
    }

    return true;
}
#pragma endregion

// array declaration
bool ruleArray(Type *type) {
    if (PRNT) printf("RULE ARRAY\n");
    Instruction *instruction;
    if (!consumeToken(LBRACKET)) return false;
    RetVal rv;
    instruction = lastInstruction;
    if (ruleExpression(&rv)) {
        deleteInstructionsAfter(instruction);
        if (!rv.isCtVal)
            tokenError(current_token, "the array size instr_stm not a constant");
        if (rv.type.typeBase != TB_INT)
            tokenError(current_token, "the array size instr_stm not an integer");
        type->nElements = rv.ctVal.i;
    } else {
        type->nElements = 0;
    }
    if (!consumeToken(RBRACKET)) return false;

    return true;
}

#pragma region expressions
bool ruleExpression(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION\n");
    if (!ruleExpressionAssign(rv)) return false;

    return true;
}

bool ruleExpressionAssign(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION ASSIGN\n");
    RetVal rve;
    Instruction *instr, *old_instruction = lastInstruction;
    Token *token_aux = current_token;

    if (ruleExpressionUnary(rv)) {
        if (consumeToken(ASSIGN)) {
            if (!ruleExpressionAssign(&rve)) return false;

            if (!rv->isLVal)
                tokenError(current_token, "cannot assign to a non-lval");
            if (rv->type.nElements > -1 || rve.type.nElements > -1)
                tokenError(current_token, "the arrays cannot be assigned");
            cast(&rv->type, &rve.type);

            instr = getRVal(&rve);
            addCastInstruction(instr, &rve.type, &rv->type);
            addInstructionII(O_INSERT, sizeof(void *) + typeArgSize(&rv->type), typeArgSize(&rv->type));
            addInstructionI(O_STORE, typeArgSize(&rv->type));

            rv->isCtVal = false;
            rv->isLVal = false;

            return true;
        }
    }

    current_token = token_aux;
    deleteInstructionsAfter(old_instruction);

    if (!ruleExpressionOr(rv)) return false;

    return true;
}

bool ruleExpressionOr(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION OR\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type, type1, type2;

    if (!ruleExpressionAnd(rv)) return false;
    while (consumeToken(OR)) {
        instr1 = rv->type.nElements < 0 ? getRVal(rv) : lastInstruction;
        type1 = rv->type;
        if (!ruleExpressionAnd(&rve)) return false;

        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be logically tested");

        if (rv->type.nElements >= 0) {
            addInstruction(O_OR_A);
        } else {
            instr2 = getRVal(&rve);
            type2 = rve.type;
            type = getArithType(&type1, &type2);
            addCastInstruction(instr1, &type1, &type);
            addCastInstruction(instr2, &type2, &type);
            switch (type.typeBase) {
                case TB_INT:
                    addInstruction(O_OR_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_OR_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_OR_C);
                    break;
            }
        }

        rv->type = createType(TB_INT, -1);
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionAnd(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION AND\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type, type1, type2;

    if (!ruleExpressionEquality(rv)) return false;
    while (consumeToken(AND)) {
        instr1 = rv->type.nElements < 0 ? getRVal(rv) : lastInstruction;
        type1 = rv->type;
        if (!ruleExpressionEquality(&rve)) return false;

        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be logically tested");

        if (rv->type.nElements >= 0) {
            addInstruction(O_AND_A);
        } 
        else { 
            instr2 = getRVal(&rve);
            type2 = rve.type;
            type = getArithType(&type1, &type2);
            addCastInstruction(instr1, &type1, &type);
            addCastInstruction(instr2, &type2, &type);
            switch (type.typeBase) {
                case TB_INT:
                    addInstruction(O_AND_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_AND_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_AND_C);
                    break;
            }
        }

        rv->type = createType(TB_INT, -1);
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionEquality(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION EQUALITY\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type, type1, type2;

    if (!ruleExpressionRelational(rv)) return false;
    while (consumeToken(EQ) || consumeToken(NE)) {
        Token *token_op = consumed_token;
        instr1 = rv->type.nElements < 0 ? getRVal(rv) : lastInstruction;
        type1 = rv->type;
        if (!ruleExpressionRelational(&rve)) return false;

        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be compared");

        if (rv->type.nElements >= 0) {
            addInstruction(token_op->type == EQ ? O_EQ_A : O_NE_A);
        } 
        else {
            instr2 = getRVal(&rve);
            type2 = rve.type;
            type = getArithType(&type1, &type2);
            addCastInstruction(instr1, &type1, &type);
            addCastInstruction(instr2, &type2, &type);

            if (token_op->type == EQ) {
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_EQ_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_EQ_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_EQ_C);
                        break;
                }
            } else {
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_NE_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_NE_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_NE_C);
                        break;
                }
            }
        }
        rv->type = createType(TB_INT, -1);
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionRelational(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION RELATIONAL\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type, type1, type2;

    if (!ruleExpressionAddSub(rv)) return false;
    while (consumeToken(LT) || consumeToken(LE) || consumeToken(GT) || consumeToken(GE)) {
        Token *token_op = consumed_token;
        instr1 = getRVal(rv);
        type1 = rv->type;
        if (!ruleExpressionAddSub(&rve)) return false;

        if (rv->type.nElements > -1 || rve.type.nElements > -1)
            tokenError(current_token, "an array cannot be compared");
        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be compared");

        instr2 = getRVal(&rve);
        type2 = rve.type;
        type = getArithType(&type1, &type2);
        addCastInstruction(instr1, &type1, &type);
        addCastInstruction(instr2, &type2, &type);

        switch (token_op->type) {
            case LT:
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_LT_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_LT_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_LT_C);
                        break;
                }
                break;
            case LE:
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_LE_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_LE_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_LE_C);
                        break;
                }
                break;
            case GT:
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_GT_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_GT_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_GT_C);
                        break;
                }
                break;
            case GE:
                switch (type.typeBase) {
                    case TB_INT:
                        addInstruction(O_GE_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_GE_D);
                        break;
                    case TB_CHAR:
                        addInstruction(O_GE_C);
                        break;
                }
                break;
            default:
                printf("plm");
                break;
        }
        rv->type = createType(TB_INT, -1);
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionAddSub(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION ADD SUB\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type1, type2;

    if (!ruleExpressionMulDiv(rv)) return false;
    while (consumeToken(ADD) || consumeToken(SUB)) {
        Token *token_op = consumed_token;
        instr1 = getRVal(rv);
        type1 = rv->type;
        if (!ruleExpressionMulDiv(&rve)) return false;

        if (rv->type.nElements > -1 || rve.type.nElements > -1)
            tokenError(current_token, "an array cannot be added or subtracted");
        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be added or subtracted");
        rv->type = getArithType(&rv->type, &rve.type);

        instr2 = getRVal(&rve);
        type2 = rve.type;
        addCastInstruction(instr1, &type1, &rv->type);
        addCastInstruction(instr2, &type2, &rv->type);

        if (token_op->type == ADD) {
            switch (rv->type.typeBase) {
                case TB_INT:
                    addInstruction(O_ADD_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_ADD_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_ADD_C);
                    break;
            }
        } else {
            switch (rv->type.typeBase) {
                case TB_INT:
                    addInstruction(O_SUB_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_SUB_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_SUB_C);
                    break;
            }
        }
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionMulDiv(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION MUL DIV\n");
    RetVal rve;
    Instruction *instr1, *instr2;
    Type type1, type2;

    if (!ruleExpressionCast(rv)) return false;
    while (consumeToken(MUL) || consumeToken(DIV)) {
        Token *token_op = consumed_token;
        instr1 = getRVal(rv);
        type1 = rv->type;
        if (!ruleExpressionCast(&rve)) return false;

        if (rv->type.nElements > -1 || rve.type.nElements > -1)
            tokenError(current_token, "an array cannot be multiplied or divided");
        if (rv->type.typeBase == TB_STRUCT || rve.type.typeBase == TB_STRUCT)
            tokenError(current_token, "a structure cannot be multiplied or divided");
        rv->type = getArithType(&rv->type, &rve.type);

        instr2 = getRVal(&rve);
        type2 = rve.type;
        addCastInstruction(instr1, &type1, &rv->type);
        addCastInstruction(instr2, &type2, &rv->type);
        if (token_op->type == MUL) {
            switch (rv->type.typeBase) {
                case TB_INT:
                    addInstruction(O_MUL_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_MUL_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_MUL_C);
                    break;
            }
        } else {
            switch (rv->type.typeBase) {
                case TB_INT:
                    addInstruction(O_DIV_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_DIV_D);
                    break;
                case TB_CHAR:
                    addInstruction(O_DIV_C);
                    break;
            }
        }
        rv->isCtVal = false;
        rv->isLVal = false;
    }

    return true;
}

bool ruleExpressionCast(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION CAST\n");
    RetVal rve;
    Instruction *old_instr = lastInstruction;
    Type type;

    if (consumeToken(LPAREN)) {
        if (!ruleTypeName(&type)) return false;
        if (!consumeToken(RPAREN)) return false;
        if (!ruleExpressionCast(&rve)) return false;

        cast(&type, &rve.type);

        if (rv->type.nElements < 0 && rv->type.typeBase != TB_STRUCT) {
            switch (rve.type.typeBase) {
                case TB_CHAR:
                    switch (type.typeBase) {
                        case TB_INT:
                            addInstruction(O_CAST_C_I);
                            break;
                        case TB_DOUBLE:
                            addInstruction(O_CAST_C_D);
                            break;
                    }
                    break;
                case TB_DOUBLE:
                    switch (type.typeBase) {
                        case TB_CHAR:
                            addInstruction(O_CAST_D_C);
                            break;
                        case TB_INT:
                            addInstruction(O_CAST_D_I);
                            break;
                    }
                    break;
                case TB_INT:
                    switch (type.typeBase) {
                        case TB_CHAR:
                            addInstruction(O_CAST_I_C);
                            break;
                        case TB_DOUBLE:
                            addInstruction(O_CAST_I_D);
                            break;
                    }
                    break;
            }

            rv->type = type;
        }
        rv->isCtVal = false;
        rv->isLVal = false;

        return true;
    }
    deleteInstructionsAfter(old_instr);

    if (!ruleExpressionUnary(rv)) return false;

    return true;
}

bool ruleExpressionUnary(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION UNARY\n");
    if (consumeToken(ADD) || consumeToken(SUB)) {
        Token *token_op = consumed_token;
        if (!ruleExpressionUnary(rv)) return false;

        if (token_op->type == SUB) {
            if (rv->type.nElements >= 0)
                tokenError(current_token, "unary '-' cannot be applied to an array");
            if (rv->type.typeBase == TB_STRUCT)
                tokenError(current_token, "unary '-' cannot be applied to a struct");

            getRVal(rv);
            switch (rv->type.typeBase) {
                case TB_CHAR:
                    addInstruction(O_NEG_C);
                    break;
                case TB_INT:
                    addInstruction(O_NEG_I);
                    break;
                case TB_DOUBLE:
                    addInstruction(O_NEG_D);
                    break;
            }
        } else {  // NOT
            if (rv->type.typeBase == TB_STRUCT)
                tokenError(current_token, "'!' cannot be applied to a struct");

            if (rv->type.nElements < 0) {
                getRVal(rv);
                switch (rv->type.typeBase) {
                    case TB_CHAR:
                        addInstruction(O_NOT_C);
                        break;
                    case TB_INT:
                        addInstruction(O_NOT_I);
                        break;
                    case TB_DOUBLE:
                        addInstruction(O_NOT_D);
                        break;
                }
            } else {
                addInstruction(O_NOT_A);
            }
            rv->type = createType(TB_INT, -1);
        }
        rv->isCtVal = false;
        rv->isLVal = false;

        return true;
    }
    if (!ruleExpressionPostfix(rv)) return false;

    return true;
}

bool ruleExpressionPostfix(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION POSTFIX\n");
    RetVal rve;

    if (!ruleExpressionPrimary(rv)) return false;
    while (1) {
        if (consumeToken(LBRACKET)) {
            if (!ruleExpression(&rve)) return false;
            if (rv->type.nElements < 0)
                tokenError(current_token, "only an array can be indexed");
            Type typeInt = createType(TB_INT, -1);
            cast(&typeInt, &rve.type);
            rv->type = rv->type;
            rv->type.nElements = -1;
            rv->isLVal = true;
            rv->isCtVal = false;
            if (!consumeToken(RBRACKET)) return false;

            addCastInstruction(lastInstruction, &rve.type, &typeInt);
            getRVal(&rve);
            if (typeBaseSize(&rv->type) != 1) {
                addInstructionI(O_PUSHCT_I, typeBaseSize(&rv->type));
                addInstruction(O_MUL_I);
            }
            addInstruction(O_OFFSET);
        } else if (consumeToken(DOT)) {
            if (!consumeToken(ID)) return false;
            Token *token_id = consumed_token;
            Symbol *struct_symbol = rv->type.s;
            Symbol *struct_member = findSymbol(&struct_symbol->members, token_id->str);
            if (!struct_member)
                tokenError(current_token, "struct %s does not have a member %s", struct_symbol->name, token_id->str);
            rv->type = struct_member->type;
            rv->isLVal = true;
            rv->isCtVal = false;

            if (struct_member->offset) {
                addInstructionI(O_PUSHCT_I, struct_member->offset);
                addInstruction(O_OFFSET);
            }
        } else {
            break;
        }
    }

    return true;
}

bool ruleExpressionPrimary(RetVal *rv) {
    if (PRNT) printf("RULE EXPRESSION PRIMARY\n");
    RetVal arg;
    Instruction *instr;

    if (consumeToken(ID)) {
        Token *token_id = consumed_token;
        Symbol *symbol = findSymbol(&symbols, token_id->str);
        if (!symbol) {
            tokenError(current_token, "undefined symbol %s", token_id->str);
        }
        rv->type = symbol->type;
        rv->isCtVal = false;
        rv->isLVal = true;

        if (consumeToken(LPAREN)) {
            Symbol **current_def_arg = symbol->args.begin;
            if (symbol->cls != CLS_FUNC && symbol->cls != CLS_EXTFUNC) {
                tokenError(current_token, "call of the non-function %s", token_id->str);
            }

            if (ruleExpression(&arg)) {
                if (current_def_arg == symbol->args.end) {
                    tokenError(current_token, "too many arguments in call");
                }

                cast(&(*current_def_arg)->type, &arg.type);
                if ((*current_def_arg)->type.nElements < 0) {
                    instr = getRVal(&arg);
                } else {
                    instr = lastInstruction;
                }
                addCastInstruction(instr, &arg.type, &(*current_def_arg)->type);
                current_def_arg++;

                while (consumeToken(COMMA)) {
                    if (!ruleExpression(&arg)) return false;
                    if (current_def_arg == symbol->args.end) {
                        tokenError(current_token, "too many arguments in call");
                    }
                    cast(&(*current_def_arg)->type, &arg.type);
                    if ((*current_def_arg)->type.nElements < 0) {
                        instr = getRVal(&arg);
                    } else {
                        instr = lastInstruction;
                    }
                    addCastInstruction(instr, &arg.type, &(*current_def_arg)->type);
                    current_def_arg++;
                }
            }
            if (!consumeToken(RPAREN)) return false;

            if (current_def_arg != symbol->args.end) {
                tokenError(current_token, "too few arguments in call");
            }
            rv->type = symbol->type;
            rv->isCtVal = 1;
            rv->isLVal = false;

            instr = addInstruction(symbol->cls == CLS_FUNC ? O_CALL : O_CALLEXT);
            instr->args[0].addr = symbol->address;

            return true;
        } else {
            if (symbol->cls == CLS_FUNC || symbol->cls == CLS_EXTFUNC) {
                tokenError(current_token, "minstr_stmsing call for function %s", token_id->str);
            }
            if (symbol->depth) {
                addInstructionI(O_PUSHFPADDR, symbol->offset);
            } else {
                addInstructionA(O_PUSHCT_A, symbol->address);
            }
        }
        return true;
    }
    Token *tk = current_token;
    if (consumeToken(CT_INT)) {
        rv->type = createType(TB_INT, -1);
        rv->ctVal.i = tk->integer;
        rv->isCtVal = 1;
        rv->isLVal = false;

        addInstructionI(O_PUSHCT_I, tk->integer);

        return true;
    }
    if (consumeToken(CT_REAL)) {
        rv->type = createType(TB_DOUBLE, -1);
        rv->ctVal.d = tk->real;
        rv->isCtVal = 1;
        rv->isLVal = false;

        instr = addInstruction(O_PUSHCT_D);
        instr->args[0].d = tk->real;

        return true;
    }
    if (consumeToken(CT_CHAR)) {
        rv->type = createType(TB_CHAR, -1);
        rv->ctVal.i = tk->integer;
        rv->isCtVal = 1;
        rv->isLVal = false;

        addInstructionI(O_PUSHCT_C, tk->integer);

        return true;
    }
    if (consumeToken(CT_STRING)) {
        rv->type = createType(TB_CHAR, 0);
        rv->ctVal.str = tk->str;
        rv->isCtVal = 1;
        rv->isLVal = false;

        addInstructionA(O_PUSHCT_A, tk->str);

        return true;
    }
    if (consumeToken(LPAREN)) {
        if (!ruleExpression(rv)) return false;
        if (!consumeToken(RPAREN)) return false;

        return true;
    }

    return false;
}
#pragma endregion

#pragma region statements
bool ruleStatementList() {
    if (PRNT) printf("RULE STATEMENT LIST\n");
    Symbol *start = symbols.end[-1];
    // printf("Start symbol: %s\n", start->name);
    if (!consumeToken(LBRACE)) return false;
    current_depth++;
    while (ruleDeclareVar() || ruleStatement())
        ;
    if (!consumeToken(RBRACE)) return false;
    current_depth--;
    deleteSymbolsAfter(&symbols, start);

    return true;
}

bool ruleStatementIf() {
    if (PRNT) printf("RULE STATEMENT IF\n");
    RetVal rv;
    Instruction *instr1, *instr2;
    if (!consumeToken(IF)) return false;
    if (!consumeToken(LPAREN)) return false;
    if (!ruleExpression(&rv)) return false;
    if (rv.type.typeBase == TB_STRUCT) {
        tokenError(current_token, "a structure cannot be logically tested");
    }
    if (!consumeToken(RPAREN)) return false;
    instr1 = createCondJmp(&rv);
    if (!ruleStatement()) return false;
    if (consumeToken(ELSE)) {
        instr2 = addInstruction(O_JMP);
        if (!ruleStatement()) return false;
        instr1->args[0].addr = instr2->next;
        instr1 = instr2;
    }
    instr1->args[0].addr = addInstruction(O_NOP);

    return true;
}

bool ruleStatementWhile() {
    if (PRNT) printf("RULE STATEMENT WHILE\n");
    RetVal rv;
    Instruction *instr1, *instr2, *old_loop = current_loop;
    current_loop = createInstruction(O_NOP);
    instr1 = lastInstruction;

    if (!consumeToken(WHILE)) return false;
    if (!consumeToken(LPAREN)) return false;
    if (!ruleExpression(&rv)) return false;
    if (rv.type.typeBase == TB_STRUCT) {
        tokenError(current_token, "a structure cannot be logically tested");
    }
    if (!consumeToken(RPAREN)) return false;
    instr2 = createCondJmp(&rv);
    if (!ruleStatement()) return false;

    addInstructionA(O_JMP, instr1->next);
    appendInstruction(current_loop);
    instr2->args[0].addr = current_loop;
    current_loop = old_loop;

    return true;
}

bool ruleStatementFor() {
    if (PRNT) printf("RULE STATEMENT FOR\n");
    RetVal rv1, rv2, rv3;
    Instruction *instr2, *instr3, *instr4, *instr_before3, *instr_before_stm, *instr_stm, *old_loop = current_loop;
    current_loop = createInstruction(O_NOP);
    if (!consumeToken(FOR)) return false;
    if (!consumeToken(LPAREN)) return false;
    if (ruleExpression(&rv1)) {
        if (typeArgSize(&rv1.type)) {
            addInstructionI(O_DROP, typeArgSize(&rv1.type));
        }
    }
    if (!consumeToken(SEMICOLON)) return false;
    instr2 = lastInstruction;
    if (ruleExpression(&rv2)) {
        instr4 = createCondJmp(&rv2);
    } else {
        instr4 = NULL;
    }
    if (rv2.type.typeBase == TB_STRUCT)
        tokenError(current_token, "a structure cannot be logically tested");
    if (!consumeToken(SEMICOLON)) return false;
    instr_before3 = lastInstruction;
    if (ruleExpression(&rv3)) {
        if (typeArgSize(&rv3.type)) {
            addInstructionI(O_DROP, typeArgSize(&rv3.type));
        }
    }
    if (!consumeToken(RPAREN)) return false;
    instr_before_stm = lastInstruction;
    if (!ruleStatement()) return false;

    if (instr_before3 != instr_before_stm) {
        instr3 = instr_before3->next;
        instr_stm = instr_before_stm->next;
        instr_before3->next = instr_stm;
        instr_stm->prev = instr_before3;
        lastInstruction->next = instr3;
        instr3->prev = lastInstruction;
        instr_before_stm->next = NULL;
        lastInstruction = instr_before_stm;
    }
    addInstructionA(O_JMP, instr2->next);
    appendInstruction(current_loop);
    if (instr4) {
        instr4->args[0].addr = current_loop;
    }
    current_loop = old_loop;

    return true;
}

bool ruleStatementBreak() {
    if (PRNT) printf("RULE STATEMENT BREAK\n");
    if (!consumeToken(BREAK)) return false;
    if (!consumeToken(SEMICOLON)) return false;

    if (!current_loop)
        tokenError(current_token, "break without for or while");
    addInstructionA(O_JMP, current_loop);

    return true;
}

bool ruleStatementReturn() {
    if (PRNT) printf("RULE STATEMENT RETURN\n");
    if (!consumeToken(RETURN)) return false;
    RetVal rv;
    Instruction *instr;
    if (ruleExpression(&rv)) {
        instr = getRVal(&rv);
        addCastInstruction(instr, &rv.type, &current_func->type);
    }
    if (current_func->type.typeBase == TB_VOID)
        tokenError(current_token, "a void function cannot return a value");
    cast(&current_func->type, &rv.type);
    if (!consumeToken(SEMICOLON)) return false;

    if (current_func->type.typeBase == TB_VOID) {
        addInstructionII(O_RET, size_args, 0);
    } else {
        addInstructionII(O_RET, size_args, typeArgSize(&current_func->type));
    }

    return true;
}

bool ruleStatementExpression() {
    if (PRNT) printf("RULE STATEMENT EXPRESSION\n");
    RetVal rv;
    if (ruleExpression(&rv)) {
        if (typeArgSize(&rv.type)) {
            addInstructionI(O_DROP, typeArgSize(&rv.type));
        }
    }
    if (!consumeToken(SEMICOLON)) return false;

    return true;
}

bool ruleStatement() {
    if (PRNT) printf("RULE STATEMENT\n");
    if (ruleStatementList()) return true;
    if (ruleStatementIf()) return true;
    if (ruleStatementWhile()) return true;
    if (ruleStatementFor()) return true;
    if (ruleStatementBreak()) return true;
    if (ruleStatementReturn()) return true;
    if (ruleStatementExpression()) return true;

    return false;
}
#pragma endregion

#pragma region declarations
bool ruleDeclareVar() {
    if (PRNT) printf("RULE DECLARE VAR\n");
    Type *type = (Type *)malloc(sizeof(Type));
    if (!ruleType(type)) return false;
    if (!consumeToken(ID)) return false;
    Token *token = consumed_token;
    if (ruleArray(type)) {
    } else {
        type->nElements = -1;
    }
    addVar(token, type);
    while (consumeToken(COMMA)) {
        if (!consumeToken(ID)) return false;
        token = consumed_token;
        if (ruleArray(type)) {
        } else {
            type->nElements = -1;
        }
        addVar(token, type);
    }
    if (!consumeToken(SEMICOLON)) return false;

    return true;
}

bool ruleDeclareStruct() {
    if (PRNT) printf("RULE DECLARE STRUCT\n");
    if (!consumeToken(STRUCT)) return false;
    if (!consumeToken(ID)) return false;
    Token *token = consumed_token;
    if (!consumeToken(LBRACE)) return false;
    if (findSymbol(&symbols, token->str))
        tokenError(current_token, "symbol redefinition: %s", token->str);
    current_struct = addSymbol(&symbols, token->str, CLS_STRUCT);
    initSymbols(&current_struct->members);
    offset = 0;
    while (ruleDeclareVar()) {
    }
    if (!consumeToken(RBRACE)) return false;
    if (!consumeToken(SEMICOLON)) return false;
    current_struct = NULL;

    return true;
}

bool ruleFuncParam() {
    if (PRNT) printf("RULE FUNC PARAM\n");
    Type *type = (Type *)malloc(sizeof(Type));
    if (!ruleType(type)) return false;
    if (!consumeToken(ID)) return false;
    Token *token = consumed_token;
    if (ruleArray(type)) {
    } else {
        type->nElements = -1;
    }
    Symbol *symbol = addSymbol(&symbols, token->str, CLS_VAR);
    symbol->mem = MEM_ARG;
    symbol->type = *type;

    Symbol *arg = addSymbol(&current_func->args, token->str, CLS_VAR);
    arg->mem = MEM_ARG;
    arg->type = *type;

    arg->offset = offset;
    symbol->offset = offset;
    offset += typeArgSize(&symbol->type);

    return true;
}

bool ruleFuncParams() {
    if (PRNT) printf("RULE FUNC PARAMS\n");
    if (!ruleFuncParam()) return false;
    while (consumeToken(COMMA)) {
        if (!ruleFuncParam()) return false;
    }

    return true;
}

bool ruleDeclareFunc() {
    if (PRNT) printf("RULE DECLARE FUNC\n");
    Type type;
    if (!consumeToken(VOID)) {
        if (!ruleType(&type)) {
            return false;
        } else {
            if (consumeToken(MUL)) {
                type.nElements = 0;
            } else {
                type.nElements = -1;
            }
        }
    } else {
        type.typeBase = TB_VOID;
    }
    if (!consumeToken(ID)) return false;
    Token *token_id = consumed_token;
    size_args = offset = 0;

    if (!consumeToken(LPAREN)) {
        return false;
    }
    if (findSymbol(&symbols, token_id->str)) {
        tokenError(current_token, "symbol redefinition: %s", token_id->str);
    }
    current_func = addSymbol(&symbols, token_id->str, CLS_FUNC);
    initSymbols(&current_func->args);
    current_func->type = type;
    current_depth++;
    ruleFuncParams();
    if (!consumeToken(RPAREN)) return false;
    current_depth--;
    current_func->address = addInstruction(O_ENTER);
    size_args = offset;
    for (Symbol **ps = symbols.begin; ps != symbols.end; ps++) {
        if ((*ps)->mem == MEM_ARG) {
            (*ps)->offset -= size_args + 2 * sizeof(void *);
        }
    }
    offset = 0;

    if (!ruleStatementList()) return false;

    deleteSymbolsAfter(&symbols, current_func);

    ((Instruction *)current_func->address)->args[0].i = offset;
    if (current_func->type.typeBase == TB_VOID) {
        addInstructionII(O_RET, size_args, 0);
    }

    current_func = NULL;

    return true;
}
#pragma endregion

// code
bool ruleCode() {
    Instruction *mainCall = addInstruction(O_CALL);
    addInstruction(O_HALT);
    while (apply(ruleDeclareStruct) || apply(ruleDeclareFunc) || apply(ruleDeclareVar)) {
    }
    if (!consumeToken(END)) return false;

    mainCall->args[0].addr = requireSymbol(&symbols, "main")->address;

    return true;
}

void predefineFunctions() {
    Symbol *symbol;

    // put_s
    symbol = addExtFunc("put_s", createType(TB_VOID, -1), put_s);
    addFuncArg(symbol, "s", createType(TB_CHAR, 0));
    // get_s
    symbol = addExtFunc("get_s", createType(TB_VOID, -1), get_s);
    addFuncArg(symbol, "s", createType(TB_CHAR, 0));

    // put_i
    symbol = addExtFunc("put_i", createType(TB_VOID, -1), put_i);
    addFuncArg(symbol, "i", createType(TB_INT, -1));
    // get_i
    symbol = addExtFunc("get_i", createType(TB_INT, -1), get_i);

    // put_d
    symbol = addExtFunc("put_d", createType(TB_VOID, -1), put_d);
    addFuncArg(symbol, "d", createType(TB_DOUBLE, -1));
    // get_d
    symbol = addExtFunc("get_d", createType(TB_DOUBLE, -1), get_d);

    // put_c
    symbol = addExtFunc("put_c", createType(TB_VOID, -1), put_c);
    addFuncArg(symbol, "c", createType(TB_CHAR, -1));
    // get_c
    symbol = addExtFunc("get_c", createType(TB_CHAR, -1), get_c);

    // seconds
    symbol = addExtFunc("seconds", createType(TB_DOUBLE, -1), seconds);
}

void analyzeDomain(Token *tokens) {
    current_token = tokens;
    initSymbols(&symbols);
    predefineFunctions();

    ruleCode();
}