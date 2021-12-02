#include <iostream>
#include "bits.h"
#include <string>

#define XBITS 8
#define YBITS 2

#define BITS XBITS+YBITS

using namespace std;

Bits<BITS> Ms[XBITS];

string line(){
    string printString = "";
    for (unsigned i = 0 ; i < BITS + 5 ; i++){
        printString += char(196);
    }
    printString += "\n";
    return printString;
}

void Ms_calc(Bits<XBITS> X, unsigned Y){
    for (unsigned i = 0 ; i < XBITS ; i++){
        Ms[i] = ( X[i] * Y ) << i;
    }

    for (unsigned i = 0 ; i < XBITS ; i++){
        cout << "M" << i<< ": " << Ms[i] << "\n";
    }
    cout << "\n";
}

void CSA(Bits<BITS> M2, Bits<BITS> M1, Bits<BITS> M0, Bits<BITS> &c, Bits<BITS> &z){
    cout << "X: " << M0 << " |\n";
    cout << "Y: " << M1 << " | +\n";
    cout << "S: " << M2 << " |\n";
    for (unsigned bit = 0 ; bit < BITS ; bit++){
        z[bit] = M0[bit] ^ M1[bit] ^ M2[bit];
        c[bit] = M0[bit]&M1[bit] | M1[bit]&M2[bit] | M2[bit]&M0[bit];
    }
    cout << line();
    cout << "Z: " << z << "\n";
    cout << "C: " << c << "\n\n";
    c = c*2;
}

Bits<BITS> CPA(Bits<BITS> X, Bits<BITS> Y){
    Bits<BITS> P;
    cout << "X: " << X << " |\n";
    cout << "Y: " << Y << " | +\n";
    bool c = 0;
    for (unsigned i = 0 ; i < BITS ; i++){
        P[i] = X[i] ^ Y[i] ^ c;
        c = X[i]&Y[i] | X[i]&c | Y[i]&c;
    }
    cout << line();
    cout << "P: " << P << "\n";
    return P;
}

void multiplier(unsigned X, unsigned Y){
    Ms_calc(X, Y);

    Bits<BITS> c1, z1, c2, z2, c3, z3, c4, z4, c5, z5, C, Z;
    CSA(Ms[2], Ms[1], Ms[0], c1, z1);
    CSA(Ms[5], Ms[4], Ms[3], c2, z2);

    CSA(z2, c1, z1, c3, z3);
    CSA(Ms[7], Ms[6], c2, c4, z4);

    CSA(z4, c3, z3, c5, z5);

    CSA(c4, c5, z5, C, Z);
    Bits<BITS> P = CPA(C, Z);
}

int main(){
    multiplier(243, -1);
}