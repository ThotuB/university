// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    //__asm {
    //    mov ax, 0x1000
    //    mov ds, ax
    //    mov si, 0

    //    mov ax, 0x4000
    //    mov es, ax
    //    mov di, 0

    //    mov cx, 0x8000      // sets cx 0x8000
    //    rep;  movsw         // moves: ds:[si] -> es:[di] - cx times

    //    mov al, 0x00
    //    out 0x20, al
    //}
    char a;

    __asm {
        mov eax, 0x00ff
        inc al
        mov a, ah
    }

    std::cout << a;
}