#include "symbol.h"

unsigned current_depth = 0;

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

        if (symbols->begin == NULL)
            err("not enough memory");

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
    if (symbols->begin == NULL)
        return;
    
    for (Symbol **p = symbols->begin; p != symbols->end; p++) {
        if (*p == s) {
            symbols->end = p;
            return;
        }
    }
}