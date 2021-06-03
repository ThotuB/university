#include <iostream>
#include "bits.h"
#include <string>

#define XBITS 8
#define YBITS 8
#define LOGBITS 4

using namespace std;

int Booth_Case(bool Q1, bool Q0, bool R){
    if ( ( !Q1 && !Q0 && R ) || ( !Q1 && Q0 && !R ) ){
        return 1;
    }
    if ( ( Q1 && Q0 && !R ) || ( Q1 && !Q0 && R ) ){
        return -1;
    }
    return 0;
}

void Modified_Booth(int Xnr, int Xe, int Ynr, int Ye, bool integers){
BEGIN:      Bits<YBITS> A; Bits<LOGBITS> COUNT;
            bool R = 0; bool OVR = 0;
INPUT:      Bits<YBITS> M(Ynr, Ye, integers);
            Bits<XBITS+1> Q(Xnr, Xe, integers);
            cout << COUNT.to_uint() << "\t" << OVR << "|" << A << " " << Q << "|" << R << " " << M << "\n";
TEST1:      switch ( Booth_Case(Q[1], Q[0], R) ){
                case 1:
                    A += M;
                    R = 0;
                    cout<<"\t +"<<M<<"\n\t  "<<A<<"\n";
                    break;
                case -1:
                    A -= M;
                    R = 1;
                    cout<<"\t -"<<M<<"\n\t  "<<A<<"\n";
                    break;
            }
TEST2:      if ( COUNT == XBITS-1 ) goto ISINT;
RSHFT:      Q.RSH(A[0]); A.RSH(A[7] ^ OVR);
 INCR:      COUNT += 1; 
            cout << COUNT.to_uint() << "\t" << OVR << "|" << A << " " << Q << "|" << R << "\n";
            goto TEST1;
ISINT:      if ( integers ) {Q.RSH(A[0]); A.RSH(A[7] ^ OVR); goto COUT;}
            Q[0] = 0;
 COUT:      cout << "\t  " << A;
            cout << Q << "\n";

}

int main(){
    Modified_Booth(-103, 0, -123, 0, 1);
}