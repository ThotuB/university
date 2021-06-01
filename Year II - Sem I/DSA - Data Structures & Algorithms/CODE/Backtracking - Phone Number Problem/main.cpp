#include <iostream>
#include <fstream>

using namespace std;

ofstream fout("out.txt");

void print_stack(int *stack, unsigned size){
    for (unsigned i = 0 ; i < size ; i++){
        fout << stack[i] << " ";
    }
    fout << "\n";
}

bool is_solution(int *stack, unsigned size){
    unsigned zeroAlone = 0;
    unsigned zeroPair = 0;

    for (unsigned i = 3 ; i < 10 ; i++){
        if ( stack[i] == 0 ){
            if ( stack[i-1] == 0 ){
                zeroPair++;
                zeroAlone--;
            }
            else{
                zeroAlone++;
            }
        }
    }

    return (zeroAlone == 1 && zeroPair == 1);
}

void phone_number_brute_new(int *phoneNr, unsigned step = 3){
    if ( step == 10 ){
        if ( is_solution(phoneNr, 10) ){
            print_stack(phoneNr, 10);
        }
    }
    else {
        for (unsigned d = 0 ; d < 10 ; d++){
            if ( step == 4 ){
                phone_number_brute_new(phoneNr, step+1);
            }
            else {
                phoneNr[step] = d;
                phone_number_brute_new(phoneNr, step+1);
                phoneNr[step] = -1;
            }
        }
    }
}

void phone_number_brute_old(int *phoneNr, unsigned step = 3){
    for (unsigned d = 0 ; d < 10 ; d++){
            if ( step == 4 ){
                phone_number_brute_old(phoneNr, step+1);
            }
            else {
                phoneNr[step] = d;
                if ( step+1 == 10 ) {
                    if ( is_solution(phoneNr, 10) ){
                        print_stack(phoneNr, 10);
                    }
                }
                else {
                    phone_number_brute_old(phoneNr, step+1);
                }
                phoneNr[step] = -1;
            }
        }
}

int main(){
    int phoneNr[10] = {0, 7, 2, -1, 4, -1, -1, -1, -1, -1};

    phone_number_brute_old(phoneNr);

    return 0;
}