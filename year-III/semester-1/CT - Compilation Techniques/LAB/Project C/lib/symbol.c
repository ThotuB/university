#include "symbol.h"

#include <stdio.h>
#include <string.h>

unsigned current_depth = 0;

void printType(Type *type) {
    if (type->nElements > -1) {
        printf("array of ");
    }
    switch (type->typeBase) {
        case TB_CHAR:
            printf("char");
            break;
        case TB_INT:
            printf("int");
            break;
        case TB_DOUBLE:
            printf("double");
            break;
        case TB_STRUCT:
            printf("struct %s", type->s->name);
            break;
        case TB_VOID:
            printf("void");
            break;
    }
    printf("\n");
}

void printSymbol(Symbol *symbol) {
    if (symbol == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Symbol: %s\n", symbol->name);
    // printf(" - class: %d\n", symbol->cls);
    // printf(" - memory: %d\n", symbol->mem);
    // printf(" - depth: %d\n", symbol->depth);
    // printf(" - type: %d\n", symbol->type.typeBase);
    // printf(" - number of elements: %d\n", symbol->type.nElements);
    // printf(" - struct: %s\n", symbol->type.s->name);
}

void printSymbols(Symbols *symbols) {
    printf("Symbols (%ld):\n", symbols->end - symbols->begin);
    for (Symbol **i = symbols->begin; i < symbols->end; i++) {
        printSymbol(*i);
    }
}

void initSymbols(Symbols *symbols) {
    symbols->begin = NULL;
    symbols->end = NULL;
    symbols->after = NULL;
}

Symbol *addSymbol(Symbols *symbols, const char *name, int cls) {
    Symbol *s;
    if (symbols->end == symbols->after) {  // create more room
        int count = symbols->after - symbols->begin;
        int n = count * 2;  // double the room
        if (n == 0)
            n = 1;  // needed for the initial case

        symbols->begin = (Symbol **)realloc(symbols->begin, n * sizeof(Symbol *));

        if (symbols->begin == NULL) {
            error("not enough memory");
        }
        symbols->end = symbols->begin + count;
        symbols->after = symbols->begin + n;
    }
    SAFE_ALLOC(s, Symbol);

    *symbols->end++ = s;
    s->name = name;
    s->cls = cls;
    s->depth = current_depth;

    return s;
}

void deleteSymbolsAfter(Symbols *symbols, Symbol *s) {
    if (symbols->begin == NULL) {
        return;
    }
    for (Symbol **i = symbols->begin; i <= symbols->end; i++) {
        if (*i == s) {
            symbols->end = i + 1;
            break;
        }
    }
}

// Find a symbol by name from right to left
Symbol *findSymbol(Symbols *symbols, const char *name) {
    if (symbols->begin == NULL) {
        return NULL;
    }
    for (Symbol **p = symbols->end - 1; p >= symbols->begin; p--) {
        if (strcmp((*p)->name, name) == 0) {
            return *p;
        }
    }
    return NULL;
}

Symbol *requireSymbol(Symbols *symbols, const char *name) {
    Symbol *s = findSymbol(symbols, name);
    if (s == NULL) {
        error("undefined symbol: %s", name);
    }
    return s;
}

Type createType(int typeBase, int nElements) {
    Type t;
    t.typeBase = typeBase;
    t.nElements = nElements;
    return t;
}

int typeBaseSize(Type *type) {
    int size = 0;
    Symbol **symbol_iterator;

    switch (type->typeBase) {
        case TB_INT:
            size = sizeof(long int);
            break;

        case TB_DOUBLE:
            size = sizeof(double);
            break;

        case TB_CHAR:
            size = sizeof(char);
            break;

        case TB_STRUCT:
            for (symbol_iterator = type->s->members.begin; symbol_iterator != type->s->members.end; symbol_iterator++) {
                size += typeFullSize(&(*symbol_iterator)->type);
            }
            break;

        case TB_VOID:
            size = 0;
            break;

        default:
            error("invalid typeBase: %d", type->typeBase);
    }
    return size;
}

int typeFullSize(Type *type) {
    return typeBaseSize(type) * (type->nElements > 0 ? type->nElements : 1);
}

int typeArgSize(Type *type) {
    if (type->nElements >= 0) {
        return sizeof(void *);
    }
    return typeBaseSize(type);
}
