#include <stdio.h>
#include <Windows.h>

int main() {
    int a = 0;

    __asm {
        mov a, 1;
    }

    printf("%d\n", a);
}