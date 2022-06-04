#ifndef VALUE_H
#define VALUE_H

#include "symbol.h"

typedef union {
    long int i;       // int, char
    double d;         // double
    const char *str;  // char[]
} CtVal;

typedef struct {
    Type type;    // type of the result
    int isLVal;   // if it is a LVal
    int isCtVal;  // if it is a constant value (int, real, char, char[])
    CtVal ctVal;  // the constat value
} RetVal;

void printValue(RetVal *rv);

void cast(Type *dst, Type *src);

Symbol *addExtFunc(const char *name, Type type, void *addr);

Symbol *addFuncArg(Symbol *func, const char *name, Type type);

Type getArithType(Type *s1, Type *s2);

#endif