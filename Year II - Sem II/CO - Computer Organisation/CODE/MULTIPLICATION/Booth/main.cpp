#include <iostream>
#include "bits.h"
#include <string>

#define XBITS 6
#define YBITS 6
#define LOGBITS 4

using namespace std;

void Booth(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS> A; Bits<LOGBITS> COUNT; bool Qbit=0;
INPUT:      Bits<YBITS> M(Ynr, Ye, integers);
            Bits<XBITS> Q(Xnr, Xe, integers);
            cout << " " << A << " " << Q << Qbit << " " << M << "\n";
TEST1:      if ( Q[0] == 0 && Qbit == 1 ) {A += M; cout<<"+"<<M<<"\n "<<A<<"\n"; goto TEST2;}
            if ( Q[0] == 1 && Qbit == 0 ) {A -= M; cout<<"-"<<M<<"\n "<<A<<"\n";}
TEST2:      if ( COUNT == XBITS-1 ) goto ISINT;
RSHFT:      Qbit=Q[0]; Q.RSH(A[0]); A.RSH(A[YBITS-1]);
            cout << " " << A << " " << Q << Qbit << "\n";
 INCR:      COUNT += 1; goto TEST1;
ISINT:      if ( integers ) {Q.RSH(A[0]); A.RSH(A[YBITS-1]); goto COUT;}
            Q[0] = 0;
 COUT:      cout << " " << A;
            cout << Q;

}

int main(){
    Booth(-19, 0, -13, 0, 1);
}