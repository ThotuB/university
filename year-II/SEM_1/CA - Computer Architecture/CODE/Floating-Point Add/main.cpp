#include <iostream>
#include "bits.h"
#include <string>

#define EXP 3
#define MAN 4

using namespace std;

void FP_Add(int Xe, int Xm, int Ye, int Ym){
BEGIN:      bool A_COUT=0; bool ERROR=0;
INPUT:      Bits<EXP> E1(Xe); Bits<MAN+1> A(Xm);
            Bits<EXP> E2(Ye); Bits<MAN+1> B(Ym);
            cout << A << " " << B << "\n";
COMPARE:    Bits<EXP> E = E1 - E2;
            cout << E << "=" << E1 << "-" << E2 << "\n";
ALIGN:      if ( E < 0 ) { 
                A.RSH(0);
                E += 1; 
                goto ALIGN; 
            }
            if ( E > 0 ) { 
                B.RSH(0); 
                E -= 1; 
                goto ALIGN; 
            }
            cout << A << " " << B << "\n";
ADDSUB:     A = A + B; 
            E = Bits<EXP>::max(E1, E2);
            cout << A << " " << B << "\n";
// OVRFLOW:    if ( A_COUT == 1 ){
//                 if ( E == E_MAX ) 
//                     goto ERROR;
//                 A.RSH(0); 
//                 E += 1; 
//                 goto END;
//             } 
// ZERO:       if ( A == 0 ) {
//                 E = 0; 
//                 goto END;
//             }
// NORMALIZE:  if ( Bits::isNormalized(A) ) 
//                 goto END;
// UNDRFLOW:   if ( E > Emin ){ 
//                 A.LSH(0); E -= 1; 
//                 goto NORMALIZE; 
//             }
// ERROR:      ERROR = 1;
// END:
}

int main(){
    FP_Add(2, 9, 4, 15);
}