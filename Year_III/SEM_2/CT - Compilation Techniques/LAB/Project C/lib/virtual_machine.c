#include "virtual_machine.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "instruction.h"
#include "time.h"
#include "token.h"

#define PRNT 0

// push & pop
void push_d(double d) {
    if (SP + sizeof(double) > stack_end)
        error("out of stack\n");
    *(double *)SP = d;
    SP += sizeof(double);
}

double pop_d() {
    SP -= sizeof(double);
    if (SP < stack)
        error("not enough stack bytes for popd\n");
    return *(double *)SP;
}

void push_a(void *a) {
    if (SP + sizeof(void *) > stack_end)
        error("out of stack\n");
    *(void **)SP = a;
    SP += sizeof(void *);
}

void *pop_a() {
    SP -= sizeof(void *);
    if (SP < stack)
        error("not enough stack bytes for popa\n");
    return *(void **)SP;
}

void push_c(char c) {
    if (SP + sizeof(char) > stack_end)
        error("out of stack\n");
    *(char *)SP = c;
    SP += sizeof(char);
}

char pop_c() {
    SP -= sizeof(char);
    if (SP < stack)
        error("not enough stack bytes for popc\n");
    return *(char *)SP;
}

void push_i(long int i) {
    if (SP + sizeof(long int) > stack_end)
        error("out of stack\n");
    *(long int *)SP = i;
    SP += sizeof(long int);
}

long int pop_i() {
    SP -= sizeof(long int);
    if (SP < stack)
        error("not enough stack bytes for popi\n");
    return *(long int *)SP;
}

//

void *allocGlobal(int size) {
    void *p = globals + numGlobals;

    if (numGlobals + size > GLOBAL_SIZE) {
        error("insufficient globals space\n");
    }
    numGlobals += size;

    return p;
}

// predefined functions
void put_i() {
    printf(">> %ld\n", pop_i());
}

void get_i() {
    int i;
    printf("<< ");
    scanf("%d", &i);
    push_i(i);
}

void put_d() {
    printf(">> %g\n", pop_d());
}

void get_d() {
    double d;
    printf("<< ");
    scanf("%lf", &d);
    push_d(d);
}

void put_s() {
    printf(">> %s\n", (char *)pop_a());
}

void get_s() {
    char *s = malloc(256);
    printf("<< ");
    scanf("%s", s);
    push_a(s);
}

void put_c() {
    printf(">> %c\n", pop_c());
}

void get_c() {
    char c;
    printf("<< ");
    scanf("%c", &c);
    push_c(c);
}

void seconds() {
    push_d(time(NULL));
}

// RUN

void run_vm(Instruction *IP) {
    char charVal1, charVal2;
    long int intVal1, intVal2;
    double doubleVal1, doubleVal2;
    char *addrVal1, *addrVal2;

    char *FP = 0, *oldSP;
    SP = stack;
    stack_end = stack + STACK_SIZE;

    while (1) {
        if ( 0 ) printf("%p / %ld\n", IP, SP - stack);

        switch (IP->opcode) {
            // arithmetic ops
            case O_ADD_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("ADD_C\t%c + %c -> %c\n", charVal2, charVal1, charVal2 + charVal1);

                push_c(charVal2 + charVal1);
                IP = IP->next;
                break;

            case O_ADD_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("ADD_D\t%g + %g -> %g\n", doubleVal2, doubleVal1, doubleVal2 + doubleVal1);

                push_d(doubleVal2 + doubleVal1);
                IP = IP->next;
                break;

            case O_ADD_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("ADD_I\t%ld + %ld -> %ld\n", intVal2, intVal1, intVal2 + intVal1);

                push_i(intVal2 + intVal1);
                IP = IP->next;
                break;

            case O_SUB_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("SUB_C\t%c - %c -> %c\n", charVal2, charVal1, charVal2 - charVal1);

                push_c(charVal2 - charVal1);
                IP = IP->next;
                break;

            case O_SUB_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("SUB_D\t%g - %g -> %g\n", doubleVal2, doubleVal1, doubleVal2 - doubleVal1);

                push_d(doubleVal2 - doubleVal1);
                IP = IP->next;
                break;

            case O_SUB_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("SUB_I\t%ld - %ld -> %ld\n", intVal2, intVal1, intVal2 - intVal1);

                push_i(intVal2 - intVal1);
                IP = IP->next;
                break;

            case O_MUL_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("MUL_C\t%c * %c -> %c\n", charVal2, charVal1, charVal2 * charVal1);

                push_c(charVal2 * charVal1);
                IP = IP->next;
                break;

            case O_MUL_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("MUL_D\t%g * %g -> %g\n", doubleVal2, doubleVal1, doubleVal2 * doubleVal1);

                push_d(doubleVal2 * doubleVal1);
                IP = IP->next;
                break;

            case O_MUL_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("MUL_I\t%ld * %ld -> %ld\n", intVal2, intVal1, intVal2 * intVal1);

                push_i(intVal2 * intVal1);
                IP = IP->next;
                break;

            case O_DIV_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("DIV_C\t%c / %c -> %c\n", charVal2, charVal1, charVal2 / charVal1);

                push_c(charVal2 / charVal1);
                IP = IP->next;
                break;

            case O_DIV_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("DIV_D\t%g / %g -> %g\n", doubleVal2, doubleVal1, doubleVal2 / doubleVal1);

                push_d(doubleVal2 / doubleVal1);
                IP = IP->next;
                break;

            case O_DIV_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("DIV_I\t%ld / %ld -> %ld\n", intVal2, intVal1, intVal2 / intVal1);

                push_i(intVal2 / intVal1);
                IP = IP->next;
                break;

            case O_NEG_C:
                charVal1 = pop_c();

                if (PRNT) printf("NEG_C\t-%c -> %c\n", charVal1, -charVal1);

                push_c(-charVal1);
                IP = IP->next;
                break;

            case O_NEG_D:
                doubleVal1 = pop_d();

                if (PRNT) printf("NEG_D\t-%g -> %g\n", doubleVal1, -doubleVal1);

                push_d(-doubleVal1);
                IP = IP->next;
                break;

            case O_NEG_I:
                intVal1 = pop_i();

                if (PRNT) printf("NEG_I\t-%ld -> %ld\n", intVal1, -intVal1);

                push_i(-intVal1);
                IP = IP->next;
                break;

            // arithmetic ops
            case O_EQ_A:
                addrVal1 = pop_a();
                addrVal2 = pop_a();

                if (PRNT) printf("EQ_A\t%p == %p -> %d\n", addrVal2, addrVal1, addrVal2 == addrVal1);

                push_i(addrVal2 == addrVal1);
                IP = IP->next;
                break;

            case O_EQ_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("EQ_C\t%c == %c -> %d\n", charVal2, charVal1, charVal2 == charVal1);

                push_i(charVal2 == charVal1);
                IP = IP->next;
                break;

            case O_EQ_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("EQ_D\t%g == %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 == doubleVal1);

                push_i(doubleVal2 == doubleVal1);
                IP = IP->next;
                break;

            case O_EQ_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("EQ_I\t%ld == %ld -> %d\n", intVal2, intVal1, intVal2 == intVal1);

                push_i(intVal2 == intVal1);
                IP = IP->next;
                break;

            case O_NE_A:
                addrVal1 = pop_a();
                addrVal2 = pop_a();

                if (PRNT) printf("NE_A\t%p != %p -> %d\n", addrVal2, addrVal1, addrVal2 != addrVal1);

                push_i(addrVal2 != addrVal1);
                IP = IP->next;
                break;

            case O_NE_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("NE_C\t%c != %c -> %d\n", charVal2, charVal1, charVal2 != charVal1);

                push_i(charVal2 != charVal1);
                IP = IP->next;
                break;

            case O_NE_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("NE_D\t%g != %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 != doubleVal1);

                push_i(doubleVal2 != doubleVal1);
                IP = IP->next;
                break;

            case O_NE_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("NE_I\t%ld != %ld -> %d\n", intVal2, intVal1, intVal2 != intVal1);

                push_i(intVal2 != intVal1);
                IP = IP->next;
                break;

            case O_GT_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("GT_C\t%c (%d) > %c (%d) -> %d\n", charVal2, charVal2, charVal1, charVal1, charVal2 > charVal1);

                push_i(charVal2 > charVal1);
                IP = IP->next;
                break;

            case O_GT_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("GT_D\t%g > %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 > doubleVal1);

                push_i(doubleVal2 > doubleVal1);
                IP = IP->next;
                break;

            case O_GT_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("GT_I\t%ld > %ld -> %d\n", intVal2, intVal1, intVal2 > intVal1);

                push_i(intVal2 > intVal1);
                IP = IP->next;
                break;

            case O_GE_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("GE_C\t%c (%d) >= %c (%d) -> %d\n", charVal2, charVal2, charVal1, charVal1, charVal2 >= charVal1);

                push_i(charVal2 >= charVal1);
                IP = IP->next;
                break;

            case O_GE_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("GE_D\t%g >= %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 >= doubleVal1);

                push_i(doubleVal2 >= doubleVal1);
                IP = IP->next;
                break;

            case O_GE_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("GE_I\t%ld >= %ld -> %d\n", intVal2, intVal1, intVal2 >= intVal1);

                push_i(intVal2 >= intVal1);
                IP = IP->next;
                break;

            case O_LT_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("LT_C\t%c (%d) < %c (%d) -> %d\n", charVal2, charVal2, charVal1, charVal1,charVal2 < charVal1);

                push_i(charVal2 < charVal1);
                IP = IP->next;
                break;

            case O_LT_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("LT_D\t%g < %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 < doubleVal1);

                push_i(doubleVal2 < doubleVal1);
                IP = IP->next;
                break;

            case O_LT_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("LT_I\t%ld < %ld -> %d\n", intVal2, intVal1, intVal2 < intVal1);

                push_i(intVal2 < intVal1);
                IP = IP->next;
                break;

            case O_LE_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("LE_C\t%c (%d) <= %c (%d) -> %d\n", charVal2, charVal2, charVal1, charVal1, charVal2 <= charVal1);

                push_i(charVal2 <= charVal1);
                IP = IP->next;
                break;

            case O_LE_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("LE_D\t%g <= %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 <= doubleVal1);

                push_i(doubleVal2 <= doubleVal1);
                IP = IP->next;
                break;

            case O_LE_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("LE_I\t%ld <= %ld -> %d\n", intVal2, intVal1, intVal2 <= intVal1);

                push_i(intVal2 <= intVal1);
                IP = IP->next;
                break;

            // conditional ops
            case O_AND_A:
                addrVal1 = pop_a();
                addrVal2 = pop_a();

                if (PRNT) printf("AND_A\t%p && %p -> %d\n", addrVal2, addrVal1, addrVal2 && addrVal1);

                push_i(addrVal2 && addrVal1);
                IP = IP->next;
                break;

            case O_AND_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("AND_C\t%c && %c -> %d\n", charVal2, charVal1, charVal2 && charVal1);

                push_i(charVal2 && charVal1);
                IP = IP->next;
                break;

            case O_AND_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("AND_D\t%g && %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 && doubleVal1);

                push_i(doubleVal2 && doubleVal1);
                IP = IP->next;
                break;

            case O_AND_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("AND_I\t%ld && %ld -> %d\n", intVal2, intVal1, intVal2 && intVal1);

                push_i(intVal2 && intVal1);
                IP = IP->next;
                break;

            case O_OR_A:
                addrVal1 = pop_a();
                addrVal2 = pop_a();

                if (PRNT) printf("OR_A\t%p || %p -> %d\n", addrVal2, addrVal1, addrVal2 || addrVal1);

                push_i(addrVal2 || addrVal1);
                IP = IP->next;
                break;

            case O_OR_C:
                charVal1 = pop_c();
                charVal2 = pop_c();

                if (PRNT) printf("OR_C\t%c || %c -> %d\n", charVal2, charVal1, charVal2 || charVal1);

                push_i(charVal2 || charVal1);
                IP = IP->next;
                break;

            case O_OR_D:
                doubleVal1 = pop_d();
                doubleVal2 = pop_d();

                if (PRNT) printf("OR_D\t%g || %g -> %d\n", doubleVal2, doubleVal1, doubleVal2 || doubleVal1);

                push_i(doubleVal2 || doubleVal1);
                IP = IP->next;
                break;

            case O_OR_I:
                intVal1 = pop_i();
                intVal2 = pop_i();

                if (PRNT) printf("OR_I\t%ld || %ld -> %d\n", intVal2, intVal1, intVal2 || intVal1);

                push_i(intVal2 || intVal1);
                IP = IP->next;
                break;

            case O_NOT_A:
                addrVal1 = pop_a();

                if (PRNT) printf("NOT_A\t!%p -> %d\n", addrVal1, !addrVal1);

                push_i(!addrVal1);
                IP = IP->next;
                break;

            case O_NOT_C:
                charVal1 = pop_c();

                if (PRNT) printf("NOT_C\t!%c -> %d\n", charVal1, !charVal1);

                push_i(!charVal1);
                IP = IP->next;
                break;

            case O_NOT_D:
                doubleVal1 = pop_d();

                if (PRNT) printf("NOT_D\t!%g -> %d\n", doubleVal1, !doubleVal1);

                push_i(!doubleVal1);
                IP = IP->next;
                break;

            case O_NOT_I:
                intVal1 = pop_i();

                if (PRNT) printf("NOT_I\t!%ld -> %d\n", intVal1, !intVal1);

                push_i(!intVal1);
                IP = IP->next;
                break;

            // jump ops
            case O_JMP:
                if (PRNT) printf("JMP\t%p\n", IP->args[0].addr);

                IP = IP->args[0].addr;
                break;

            case O_JT_A:
                addrVal1 = pop_a();

                if (PRNT) printf("JT_A\t%p <- %p\n", IP->args[0].addr, addrVal1);

                IP = addrVal1 ? IP->args[0].addr : IP->next;
                break;

            case O_JT_C:
                charVal1 = pop_c();

                if (PRNT) printf("JT_C\t%p <- %c\n", IP->args[0].addr, charVal1);

                IP = charVal1 ? IP->args[0].addr : IP->next;
                break;

            case O_JT_D:
                doubleVal1 = pop_d();

                if (PRNT) printf("JT_D\t%p <- %g\n", IP->args[0].addr, doubleVal1);

                IP = doubleVal1 ? IP->args[0].addr : IP->next;
                break;

            case O_JT_I:
                intVal1 = pop_i();

                if (PRNT) printf("JT_I\t%p <- %ld\n", IP->args[0].addr, intVal1);

                IP = intVal1 ? IP->args[0].addr : IP->next;
                break;

            case O_JF_A:
                addrVal1 = pop_a();

                if (PRNT) printf("JF_A\t%p <- !%p\n", IP->args[0].addr, addrVal1);

                IP = addrVal1 ? IP->next : IP->args[0].addr;
                break;

            case O_JF_C:
                charVal1 = pop_c();

                if (PRNT) printf("JF_C\t%p <- !%c\n", IP->args[0].addr, charVal1);

                IP = charVal1 ? IP->next : IP->args[0].addr;
                break;

            case O_JF_D:
                doubleVal1 = pop_d();

                if (PRNT) printf("JF_D\t%p <- !%g\n", IP->args[0].addr, doubleVal1);

                IP = doubleVal1 ? IP->next : IP->args[0].addr;
                break;

            case O_JF_I:
                intVal1 = pop_i();

                if (PRNT) printf("JF_I\t%p <- !%ld\n", IP->args[0].addr, intVal1);

                IP = intVal1 ? IP->next : IP->args[0].addr;
                break;

            // cast ops
            case O_CAST_C_D:
                charVal1 = pop_c();
                doubleVal1 = (double)charVal1;

                if (PRNT) printf("CAST_C_D\t(%c (%d) -> %g)\n", charVal1, charVal1, doubleVal1);

                push_d(doubleVal1);
                IP = IP->next;
                break;

            case O_CAST_C_I:
                charVal1 = pop_c();
                intVal1 = (int)charVal1;

                if (PRNT) printf("CAST_C_I\t(%c (%d) -> %ld)\n", charVal1, charVal1, intVal1);

                push_i(intVal1);
                IP = IP->next;
                break;

            case O_CAST_D_C:
                doubleVal1 = pop_d();
                charVal1 = (char)doubleVal1;

                if (PRNT) printf("CAST_D_C\t(%g -> %c (%d))\n", doubleVal1, charVal1, charVal1);

                push_c(charVal1);
                IP = IP->next;
                break;

            case O_CAST_D_I:
                doubleVal1 = pop_d();
                intVal1 = (int)doubleVal1;

                if (PRNT) printf("CAST_D_I\t(%g -> %ld)\n", doubleVal1, intVal1);

                push_i(intVal1);
                IP = IP->next;
                break;

            case O_CAST_I_C:
                intVal1 = pop_i();
                charVal1 = (char)intVal1;

                if (PRNT) printf("CAST_I_C\t(%ld -> %c (%d))\n", intVal1, charVal1, charVal1);

                push_c(charVal1);
                IP = IP->next;
                break;

            case O_CAST_I_D:
                intVal1 = pop_i();
                doubleVal1 = (double)intVal1;

                if (PRNT) printf("CAST_I_D\t(%ld -> %g)\n", intVal1, doubleVal1);

                push_d(doubleVal1);
                IP = IP->next;
                break;


            case O_CALL:
                addrVal1 = IP->args[0].addr;

                if (PRNT) printf("CALL\t%p\n", addrVal1);

                push_a(IP->next);
                IP = (Instruction *)addrVal1;
                break;

            case O_CALLEXT:
                if (PRNT) printf("CALLEXT\t%p\n", IP->args[0].addr);

                (*(void (*)())IP->args[0].addr)();
                IP = IP->next;
                break;

            case O_DROP:
                intVal1 = IP->args[0].i;

                if (PRNT) printf("DROP\t%ld\n", intVal1);

                if (SP - intVal1 < stack) {
                    error("Stack underflow\n");
                }
                SP -= intVal1;
                IP = IP->next;
                break;

            case O_ENTER:
                intVal1 = IP->args[0].i;

                if (PRNT) printf("ENTER\t%ld\n", intVal1);

                push_a(FP);
                FP = SP;
                SP += intVal1;
                IP = IP->next;
                break;

            case O_LOAD:
                intVal1 = IP->args[0].i;
                addrVal1 = pop_a();

                if (PRNT) printf("LOAD\t%ld (%p)\n", intVal1, addrVal1);

                if (SP + intVal1 >= stack_end) {
                    error("Stack overflow\n");
                }
                memcpy(SP, addrVal1, intVal1);
                SP += intVal1;
                IP = IP->next;
                break;

            case O_NOP:
                if (PRNT) printf("NOP\n");

                IP = IP->next;
                break;

            case O_HALT:
                if (PRNT) printf("HALT\n");

                return;

            case O_INSERT:
                intVal1 = IP->args[0].i;
                intVal2 = IP->args[1].i;

                if (PRNT) printf("INSERT\t%ld, %ld\n", intVal1, intVal2);

                if (SP + intVal2 > stack_end) {
                    error("Stack overflow\n");
                }
                memmove(SP - intVal1 + intVal2, SP - intVal1, intVal1);
                memmove(SP - intVal1, SP + intVal2, intVal2);
                SP += intVal2;
                IP = IP->next;
                break;

            case O_OFFSET:
                intVal1 = pop_i();
                addrVal1 = pop_a();

                if (PRNT) printf("OFFSET\t%p + %ld -> %p\n", addrVal1, intVal1, addrVal1 + intVal1);

                push_a(addrVal1 + intVal1);
                IP = IP->next;
                break;

            case O_PUSHFPADDR:
                intVal1 = IP->args[0].i;

                if (PRNT) printf("PUSHFPADDR\t%p + %ld -> %p\n", FP, intVal1, FP + intVal1);

                push_a(FP + intVal1);
                IP = IP->next;
                break;

            case O_PUSHCT_A:
                addrVal1 = IP->args[0].addr;

                if (PRNT) printf("PUSHCT_A\t%p\n", addrVal1);

                push_a(addrVal1);
                IP = IP->next;
                break;

            case O_PUSHCT_C:
                charVal1 = IP->args[0].i;

                if (PRNT) printf("PUSHCT_C\t%c\n", charVal1);

                push_c(charVal1);
                IP = IP->next;
                break;

            case O_PUSHCT_D:
                doubleVal1 = IP->args[0].d;

                if (PRNT) printf("PUSHCT_D\t%g\n", doubleVal1);

                push_d(doubleVal1);
                IP = IP->next;
                break;

            case O_PUSHCT_I:
                intVal1 = IP->args[0].i;

                if (PRNT) printf("PUSHCT_I\t%ld\n", intVal1);

                push_i(intVal1);
                IP = IP->next;
                break;

            case O_RET:
                intVal1 = IP->args[0].i;
                intVal2 = IP->args[1].i;

                if (PRNT) printf("RET\t%ld, %ld\n", intVal1, intVal2);

                oldSP = SP;
                SP = FP;
                FP = pop_a();
                IP = pop_a();

                if (SP - intVal1 < stack) {
                    error("Stack underflow\n");
                }
                SP -= intVal1;
                memmove(SP, oldSP - intVal2, intVal2);
                SP += intVal2;
                break;

            case O_STORE:
                intVal1 = IP->args[0].i;

                if (SP - (sizeof(void *) + intVal1) < stack) {
                    error("stack underflow\n");
                }

                addrVal1 = *(void **)(SP - ((sizeof(void *) + intVal1)));

                if (PRNT) printf("STORE\t%ld (%p)\n", intVal1, addrVal1);

                memcpy(addrVal1, SP - intVal1, intVal1);
                SP -= sizeof(void *) + intVal1;
                IP = IP->next;
                break;

            default:
                error("Unknown opcode %d", IP->opcode);
        }
    }
}

char *instruction_to_string[] = {
    "ADD_C", "ADD_D", "ADD_I",
    "SUB_C", "SUB_D", "SUB_I",
    "MUL_C", "MUL_D", "MUL_I",
    "DIV_C", "DIV_D", "DIV_I",
    "NEG_C", "NEG_D", "NEG_I",

    "EQ_A", "EQ_C", "EQ_D", "EQ_I",
    "NE_A", "NE_C", "NE_D", "NE_I",
    "GT_C", "GT_D", "GT_I",
    "GE_C", "GE_D", "GE_I",
    "LT_C", "LT_D", "LT_I",
    "LE_C", "LE_D", "LE_I",

    "AND_A", "AND_C", "AND_D", "AND_I",
    "OR_A", "OR_C", "OR_D", "OR_I",
    "NOT_A", "NOT_C", "NOT_D", "NOT_I",

    "JMP",
    "JT_A", "JT_C", "JT_D", "JT_I",
    "JF_A", "JF_C", "JF_D", "JF_I",

    "CAST_C_D", "CAST_C_I", "CAST_D_C", "CAST_D_I", "CAST_I_C", "CAST_I_D",

    "CALL",
    "CALLEXT",
    "DROP",
    "ENTER",

    "LOAD",
    "NOP",

    "HALT",
    "INSERT",

    "OFFSET",

    "PUSHFPADDR",
    "PUSHCT_A", "PUSHCT_C", "PUSHCT_D", "PUSHCT_I",

    "RET",
    "STORE"
};

void printInstructions(Instruction *IP) {
    for (Instruction *i = IP; i != NULL; i = i->next) {
        printf("%s\n", instruction_to_string[i->opcode]);
        if (i == lastInstruction) break;
    }
}

void printInstruction(Instruction *instruction) {
    printf("%p %s %p\n", instruction->prev, instruction_to_string[instruction->opcode], instruction->next);
}