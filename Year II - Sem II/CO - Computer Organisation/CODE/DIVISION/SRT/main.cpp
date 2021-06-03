#include <iostream>
#include "bits.hpp"
#include <string>

#define XBITS 8
#define YBITS 8
#define LOGBITS 4

using namespace std;

int Cases[2][2][2] = { { {{0}, {1}}, {{1}, {1}}}, {{{-1}, {-1}}, {{-1}, {0}}} };;

int SRT_Case(bool A8, bool A7, bool A6){
    return Cases[A8][A7][A6];
}

void SRT(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS+1> A;
            Bits<XBITS> Qi;
            Bits<LOGBITS> COUNT1; 
            Bits<LOGBITS> COUNT2;
INPUT:      Bits<YBITS> M(Ynr, Ye, integers);
            Bits<XBITS> Q(Xnr, Xe, integers);
            cout << COUNT1.to_uint() << "  " << A << " " << Q << " " << M << "\n";
TEST1:      while ( !M[7] ){
                A.LSH(Q[7]); Q.LSH(M[7]); M.LSH(0);
                COUNT2 += 1;
            }
            cout << "   " << A << " " << Q << " " << M << "\n";
TEST2:      switch ( SRT_Case(A[8], A[7], A[6]) ){
                case 0:
                    A.LSH(Q[7]); Q.LSH(0);
                    Qi.LSH(0);
                    break;
                case 1:
                    A.LSH(Q[7]); Q.LSH(1);
                    Qi.LSH(0);
                    A -= M.to_uint();
                    cout<<"  - "<<M<<"\n   "<<A<<"\n";
                    break;
                case -1:
                    A.LSH(Q[7]); Q.LSH(0);
                    Qi.LSH(1);
                    A += M.to_uint();
                    cout<<"  + "<<M<<"\n   "<<A<<"\n";
                    break;
            }
TEST3:      if ( COUNT1 == XBITS-1 ) goto CRCT;
 INCR:      COUNT1 += 1; 
            cout << COUNT1.to_uint() << "  " << A << " " << Q << "\n";
            goto TEST2;
 CRCT:      if ( A[8] ){
                A += M.to_uint();
                Q -= 1;
                cout << "C  " << A << " " << Q << "\n";
            }
SHIFT:      while ( COUNT2 != 0 ){
                A.RSH(0);
                COUNT2 -= 1;
            }
            cout << "S  " << A << " " << Q << "\n";
ISINT:      if ( integers ) {
                goto COUT;
            }
            Q[0] = 0;
 COUT:      cout << "   " << A << "|";
            cout << Q << "\n";

}

int main(){
    SRT(173, 0, 6, 0, 1);
}