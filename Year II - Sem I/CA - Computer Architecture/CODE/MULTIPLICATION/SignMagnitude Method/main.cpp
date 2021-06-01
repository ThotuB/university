#include <iostream>
#include "bits.h"
#include <string>

#define XBITS 10
#define YBITS 6
#define LOGBITS 4

using namespace std;

void SignMagnitude(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS> A; Bits<LOGBITS> COUNT;
INPUT:      Bits<YBITS> M(Ynr, Ye, integers);
            Bits<XBITS> Q(Xnr, Xe, integers);
            cout << A << " " << Q << " " << M << "\n";
TEST1:      if ( Q[0] == 0 ) goto RSHFT;
  ADD:      A += M;
            cout << A << "\n";
RSHFT:      Q.RSH(A[0]); A.RSH(0);
            cout << A << " " << Q << "\n";
 INCR:      COUNT += 1;
TEST2:      if ( COUNT != XBITS-1 ) goto TEST1;
ISINT:      if ( integers ) {bool sgn = (Q[0] ^ M[YBITS-1]); Q.RSH(A[0]); A.RSH(sgn); ; goto COUT;}
 SIGN:      A[YBITS-1] = Q[0] ^ M[YBITS-1]; Q[0] = 0;
 COUT:      cout << A;
            cout << Q;

}

int main(){
    SignMagnitude(-405, 0, 21, 0, 0);
}