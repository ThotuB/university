#include <iostream>
#include "bits.hpp"
#include <string>

#define XBITS 8
#define YBITS 8
#define LOGBITS 4

using namespace std;

int Radix4[2][2][2] = { { {{0}, {1}}, {{1}, {2}}}, {{{-2}, {-1}}, {{-1}, {0}}} };

int Booth_Case(bool Q1, bool Q0, bool Qbit){
    return Radix4[Q1][Q0][Qbit];
}

void Modified_Booth(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS+1> A; Bits<LOGBITS> COUNT;
            bool Qbit = 0;
INPUT:      Bits<YBITS+1> M(Ynr, Ye, integers);
            Bits<XBITS> Q(Xnr, Xe, integers);
            cout << COUNT.to_uint() << "  " << A << " " << Q << "|" << Qbit << " " << M << "\n";
TEST1:      switch ( Booth_Case(Q[1], Q[0], Qbit) ){
                case 1:
                    A += M;
                    cout<<"  +"<<M<<"\n   "<<A<<"\n";
                    break;
                case -1:
                    A -= M;
                    cout<<"  -"<<M<<"\n   "<<A<<"\n";
                    break;
                case 2:
                    A += M;
                    A += M;
                    cout<<" ++"<<M<<"\n   "<<A<<"\n";
                    break;
                case -2:
                    A -= M;
                    A -= M;
                    cout<<" --"<<M<<"\n   "<<A<<"\n";
                    break;
            }
TEST2:      if ( COUNT == XBITS/2-1 ) goto ISINT;
RSHFT:      Qbit = Q[0]; Q.RSH(A[0]); A.RSH(A[8]);
            Qbit = Q[0]; Q.RSH(A[0]); A.RSH(A[8]);
 INCR:      COUNT += 1; 
            cout << COUNT.to_uint() << "  " << A << " " << Q << "|" << Qbit << "\n";
            goto TEST1;
ISINT:      if ( integers ) {
                Q.RSH(A[0]); A.RSH(A[8]); 
                Q.RSH(A[0]); A.RSH(A[8]);
                goto COUT;
                }
            Q[0] = 0;
 COUT:      cout << "   " << A;
            cout << Q << "\n";

}

int main(){
    Modified_Booth(-109, 0, -75, 0, 1);
}