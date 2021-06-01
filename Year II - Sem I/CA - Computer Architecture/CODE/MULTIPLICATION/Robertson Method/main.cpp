#include <iostream>
#include "bits.h"
#include <string>

#define XBITS 10
#define YBITS 6
#define LOGBITS 4

using namespace std;

void Robertson(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS> A; Bits<LOGBITS> COUNT; bool F=0;
INPUT:      Bits<YBITS> M(Ynr, Ye, integers);
            Bits<XBITS> Q(Xnr, Xe, integers);
            cout << F << " " << A << " " << Q << " " << M << "\n";
TEST1:      if ( Q[0] == 0 ) goto RSHFT;
  ADD:      A += M; F = F | ( Q[0] & M[YBITS-1] );
            cout << F << " " << A << "\n";
RSHFT:      Q.RSH(A[0]); A.RSH(F);
            cout << F << " " << A << " " << Q << "\n";
 INCR:      COUNT += 1;
TEST2:      if ( COUNT != XBITS-1 ) goto TEST1;
TEST3:      if ( Q[0] == 0 ) goto ISINT;
CRRCT:      A -= M; Q[0] = 0;
            cout << F << " " << A << " " << Q << "\n";
ISINT:      if ( integers ) {Q.RSH(A[0]); A.RSH(A[YBITS-1]);}
 COUT:      cout << A;
            cout << Q;

}

int main(){
    Robertson(-405, 0, 21, 0, 0);
}