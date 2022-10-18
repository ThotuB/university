#include <stdio.h>

int get_i() {
    int i;
    scanf("<< %d", &i);
    return i;
}

void put_i(int i) {
    printf(">> %d\n", i);
}


char get_c() {
    char c;
    scanf("<< %c", &c);
    return c;
}

void put_c(char c) {
    printf(">> %c\n", c);
}


double get_d() {
    double d;
    scanf("<< %lf", &d);
    return d;
}

void put_d(double d) {
    printf(">> %lf\n", d);
}


char *get_s() {
    char s[100];
    scanf("<< %s", s);
    return s;
}

void put_s(char *s) {
    printf(">> %s\n", s);
}
