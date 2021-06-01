#include <iostream>

#define SIZE 5

#define XOR 2
#define OR 1
#define AND 1
#define INV 0

using namespace std;

unsigned RCA[SIZE] = {2, 5, 6, 5, 2};
unsigned Zs[SIZE][SIZE] = {0};
unsigned Cs[SIZE][SIZE+1] = {0};

void print(){
    for (unsigned i = 0 ; i < SIZE ; i++){
        for (unsigned j = 0 ; j < SIZE - i ; j++){
            cout << Cs[i][j] << "\t| " << Zs[i][j] << "\t| ";
        }
        cout << Cs[i][SIZE-i] << "\t|\n";
    }
}

void CSkA(){
    for (unsigned i = 0 ; i < SIZE ; i++){
        Cs[i][SIZE-i] = 0;
        for (int j = SIZE-i-1 ; j >= 0 ; j--){
            if ( j == SIZE-i-1 ){
                Cs[i][j] = Cs[i][j+1] + RCA[j] * (OR + AND) + ( i != 0 ) * OR;
            }
            else if ( j == 0 ) {
                Cs[i][j] = Cs[i][j+1] + RCA[j] * (OR + AND);
            }
            else {
                Cs[i][j] = Cs[i][j+1] + OR + AND;
            }

            Zs[i][j] = Cs[i][j+1] + RCA[j] * XOR;
        }
    }
}

int main(){
    CSkA();
    print();
}