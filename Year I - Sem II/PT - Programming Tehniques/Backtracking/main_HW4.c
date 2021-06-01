#include <stdio.h>
#include <stdlib.h>

#define COINS 3 // nr of coins used

unsigned coin_types[] = {1, 10, 5, 25, 100, 75, 50};  // selection of coins
                                                      // first COINS of coin_types are used
unsigned ways = 0;

void print_change(unsigned change[]){
    ways++;
    printf("%u:\t", ways);
    for (unsigned i = 0 ; i < COINS ; i++){
        if ( change[i] == 0){
            continue;
        }
        printf("%u x %uc  \t", change[i], coin_types[i]);
    }
    printf("\n");
}

void coin_problem_backtracking(int coin, unsigned sum, unsigned value){
    static unsigned change[COINS] = {0};

    if ( coin == -1 || sum >= value ){
        if ( sum == value ){
            print_change(change);
        }
    }
    else {
        for (unsigned i = 0 ; sum + i*coin_types[coin] <= value ; i++){
            change[coin] = i;
            coin_problem_backtracking( coin - 1, sum + i*coin_types[coin], value);
        }
    }
}

int main(){
    unsigned value = 132;

    coin_problem_backtracking(COINS - 1, 0, value);
}
