#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>
#include "token.h"


enum { TB_INT,
       TB_DOUBLE,
       TB_CHAR,
       TB_STRUCT,
       TB_VOID };

enum { CLS_VAR,
       CLS_FUNC,
       CLS_EXTFUNC,
       CLS_STRUCT };

enum { MEM_GLOBAL,
       MEM_ARG,
       MEM_LOCAL };

struct _Symbol;
typedef struct _Symbol Symbol;
typedef struct {
    Symbol **begin;  // the beginning of the symbols, or NULL
    Symbol **end;    // the position after the last symbol
    Symbol **after;  // the position after the allocated space
} Symbols;

typedef struct {
    int typeBase;   // TB_*
    Symbol *s;      // struct definition for TB_STRUCT
    int nElements;  // >0 array of given size, 0=array without size, <0 non array
} Type;


typedef struct _Symbol {
    const char *name;  // a reference to the name stored in a token
    int cls;           // CLS_*
    int mem;           // MEM_*
    Type type;
    int depth;  // 0-global, 1-in function, 2... - nested blocks in function
    union {
        void *address;
        int offset;
    };
    union {
        Symbols args;     // used only of functions
        Symbols members;  // used only for structs
    };
} Symbol;

void printType(Type *type);

void printSymbol(Symbol *symbol);

void printSymbols(Symbols *symbols);

void initSymbols(Symbols*);

Symbol *addSymbol(Symbols*, const char*, int );

void deleteSymbolsAfter(Symbols*, Symbol*);

Symbol *findSymbol(Symbols*, const char*);

Symbol* requireSymbol(Symbols *, const char *);

Type createType(int typeBase, int nElements);

int typeBaseSize(Type *type);

int typeFullSize(Type *type);

int typeArgSize(Type *type);

extern unsigned current_depth;
Symbol *current_struct;
Symbol *current_func;
Symbols symbols;

#endif