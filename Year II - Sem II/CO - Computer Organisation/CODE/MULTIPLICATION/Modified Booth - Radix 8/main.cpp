#include <iostream>
#include "bits.h"
#include <string>
#include <math.h>

#define XBITS 8
#define YBITS 8
#define LOGBITS 4

using namespace std;

int Radix8[2][2][2][2] = { { {{{0}, {1}}, {{1}, {2}}}, {{{2}, {3}}, {{3}, {4}}}}, 
                            {{{{-4}, {-3}}, {{-3}, {-2}}}, {{{-2}, {-1}}, {{-1}, {0}}}} };

int Booth_Case(bool Q2, bool Q1, bool Q0, bool Qbit){
    return Radix8[Q2][Q1][Q0][Qbit];
}

void Modified_Booth_Radix8(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS+2> A; Bits<LOGBITS> COUNT;
            bool Qbit = 0;
INPUT:      Bits<YBITS+2> M(Ynr, Ye, integers);
            Bits<XBITS+1> Q(Xnr, Xe, integers);
            cout << COUNT.to_uint() << "  " << A << " " << Q << "|" << Qbit << " " << M << "\n";
TEST1:      switch ( Booth_Case(Q[2], Q[1], Q[0], Qbit) ){
                case 1:
                    A += M;
                    cout<<" 1+"<<M<<"\n   "<<A<<"\n";
                    break;
                case -1:
                    A -= M;
                    cout<<" 1-"<<M<<"\n   "<<A<<"\n";
                    break;
                case 2:
                    A += M; A += M;
                    cout<<" 2+"<<M<<"\n   "<<A<<"\n";
                    break;
                case -2:
                    A -= M; A -= M;
                    cout<<" 2-"<<M<<"\n   "<<A<<"\n";
                    break;
                case 3:
                    A += M; A += M; A += M;
                    cout<<" 3+"<<M<<"\n   "<<A<<"\n";
                    break;
                case -3:
                    A -= M; A -= M; A -= M;
                    cout<<" 3-"<<M<<"\n   "<<A<<"\n";
                    break;
                case 4:
                    A += M; A += M; A += M; A += M;
                    cout<<" 4+"<<M<<"\n   "<<A<<"\n";
                    break;
                case -4:
                    A -= M; A -= M; A -= M; A -= M;
                    cout<<" 4-"<<M<<"\n   "<<A<<"\n";
                    break;
            }
TEST2:      if ( COUNT == ceil(XBITS/3.)-1 ) goto ISINT;
RSHFT:      Qbit = Q[0]; Q.RSH(A[0]); A.RSH(A[9]);
            Qbit = Q[0]; Q.RSH(A[0]); A.RSH(A[9]);
            Qbit = Q[0]; Q.RSH(A[0]); A.RSH(A[9]);
 INCR:      COUNT += 1; 
            cout << COUNT.to_uint() << "  " << A << " " << Q << "|" << Qbit << "\n";
            goto TEST1;
ISINT:      if ( integers ) {
                Q.RSH(A[0]); A.RSH(A[9]); 
                Q.RSH(A[0]); A.RSH(A[9]);
                Q.RSH(A[0]); A.RSH(A[9]);
                goto COUT;
            }
            Q[0] = 0;
 COUT:      cout << "   " << A << " ";
            cout << Q << "\n";

}

int main(){
    Modified_Booth_Radix8(-109, 0, -75, 0, 1);
}