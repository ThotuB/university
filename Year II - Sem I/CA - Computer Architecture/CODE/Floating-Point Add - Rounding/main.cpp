#include <iostream>
#include <string>
#include "bits.h"
//#include "nrs.h"

#define E 4
#define M 5

using namespace std;

void FP_addition(string nr1, string nr2){
    Bits<E, M> X(nr1);
    Bits<E, M> Y(nr2);

    X.print();
    Y.print();
}

int main(){
    FP_addition("0110001000", "1100011011");
}