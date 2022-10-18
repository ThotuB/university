X`unit`: 
:   ( `declStruct` | `declFunc` | `declVar` )* **END** ;

X`declStruct`: 
:   **STRUCT** **ID** **LACC** `declVar`* **RACC** **SEMICOLON** ;

X`declVar`:  
:   `typeBase` **ID** `arrayDecl`? ( **COMMA** **ID** `arrayDecl`? )* **SEMICOLON** ;

X`typeBase`: 
:   **INT** 
    | **DOUBLE** 
    | **CHAR** 
    | **STRUCT** **ID** ;

X`arrayDecl`: 
:   **LBRACKET** `expr`? **RBRACKET** ;

`typeName`: 
:   `typeBase` `arrayDecl`? ;

X`declFunc`: 
:   ( `typeBase` **MUL**? | **VOID** ) **ID** **LPAR** ( `funcArg` ( **COMMA** `funcArg` )* )? **RPAR** `stmCompound` ;

X`funcArg`:
:   `typeBase` **ID** `arrayDecl`? ;

`stm`: 
:   `stmCompound` 
    | **IF** **LPAR** `expr` **RPAR** `stm` ( **ELSE** `stm` )?
    | **WHILE** **LPAR** `expr` **RPAR** `stm`
    | **FOR** **LPAR** `expr`? **SEMICOLON** `expr`? **SEMICOLON** `expr`? **RPAR** `stm`
    | **BREAK** **SEMICOLON**
    | **RETURN** `expr`? **SEMICOLON**
    | `expr`? **SEMICOLON** ;

`stmCompound`: 
:   **LACC** ( `declVar` | `stm` )* **RACC** ;

X`expr`: 
:   `exprAssign` ;

X`exprAssign`: 
:   `exprUnary` **ASSIGN** `exprAssign` 
    | `exprOr` ;

X`exprOr`: 
:   `exprOr` **OR** `exprAnd` 
    | `exprAnd` ;
 
X`exprAnd`: 
:   `exprAnd` **AND** `exprEq` 
    | `exprEq` ;

X`exprEq`: 
:   `exprEq` ( **EQUAL** | **NOTEQ** ) `exprRel` 
    | `exprRel` ;

X`exprRel`: 
:   `exprRel` ( **LESS** | **LESSEQ** | **GREATER** | **GREATEREQ** ) `exprAdd` 
    | `exprAdd` ;

X`exprAdd`: 
:   `exprAdd` ( **ADD** | **SUB** ) `exprMul` 
    | `exprMul` ;

X`exprMul`: 
:   `exprMul` ( **MUL** | **DIV** ) `exprCast` 
    | `exprCast` ;

X`exprCast`: 
:   **LPAR** `typeName` **RPAR** `exprCast` 
    | `exprUnary` ;

X`exprUnary`: 
:   ( **SUB** | **NOT** ) `exprUnary` 
    | `exprPostfix` ;

X`exprPostfix`: 
:    `exprPostfix` **LBRACKET** `expr` **RBRACKET**
    | `exprPostfix` **DOT** **ID** 
    | `exprPrimary` ;

X`exprPrimary`: 
:    **ID** ( **LPAR** ( `expr` ( **COMMA** `expr` )* )? **RPAR** )?
    | **CT_INT**
    | **CT_REAL** 
    | **CT_CHAR** 
    | **CT_STRING** 
    | **LPAR** `expr` **RPAR** ;