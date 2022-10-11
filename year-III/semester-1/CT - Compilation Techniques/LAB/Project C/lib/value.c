#include "value.h"

#include "domain_analyzer.h"
#include "token.h"
#include <stdio.h>

void printValue(RetVal *rv) {
    if (rv == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Type: ");
    printType(&rv->type);
    if (rv->isCtVal) {
        printf("CtVal\n");
    }
    else if (rv->isLVal) {
        printf("LVal\n");
    }
    else {
        printf("Val\n");
    }
}

void cast(Type *dst, Type *src) {
    if (src->nElements > -1) {
        if (dst->nElements > -1) {
            if (src->typeBase != dst->typeBase)
                tokenError(current_token, "an array cannot be converted to an array of another type");
        } else {
            tokenError(current_token, "an array cannot be converted to a non-array");
        }
    } else {
        if (dst->nElements > -1) {
            tokenError(current_token, "a non-array cannot be converted to an array");
        }
    }
    switch (src->typeBase) {
        case TB_CHAR:
        case TB_INT:
        case TB_DOUBLE:
            switch (dst->typeBase) {
                case TB_CHAR:
                    src->typeBase = TB_CHAR;
                    return;
                case TB_INT:
                    src->typeBase = TB_INT;
                    return;
                case TB_DOUBLE:
                    src->typeBase = TB_DOUBLE;
                    return;
            }
        case TB_STRUCT:
            if (dst->typeBase == TB_STRUCT) {
                if (src->s != dst->s)
                    tokenError(current_token, "a structure cannot be converted to another one");
                return;
            }
    }
    tokenError(current_token, "incompatible types");
}

Symbol *addExtFunc(const char *name, Type type, void *addr) {
    current_depth++;
    Symbol *s = addSymbol(&symbols, name, CLS_EXTFUNC);
    current_depth--;
    s->type = type;
    s->address = addr;

    initSymbols(&s->args);

    return s;
}

Symbol *addFuncArg(Symbol *func, const char *name, Type type) {
    Symbol *a = addSymbol(&func->args, name, CLS_VAR);
    a->type = type;

    return a;
}

Type getArithType(Type *s1, Type *s2) {
    Type type;
    type.nElements = -1;
    
    if (s1->typeBase == TB_DOUBLE || s2->typeBase == TB_DOUBLE) {
        type.typeBase = TB_DOUBLE;
    } 
    else if (s1->typeBase == TB_INT || s2->typeBase == TB_INT) {
        type.typeBase = TB_INT;
    } 
    else {
        type.typeBase = TB_CHAR;
    }

    return type;
}