#include <iostream>

#define PRNT_STYLE 1    // 0 - NORMAL PRINT
                        // 1 - FANCY PRINT

using namespace std;

// BANKNOTE
struct Banknote {
    unsigned number;
    unsigned value;
};

unsigned get_notes(Banknote walletFROM[], unsigned size){
    unsigned notes = 0;

    for (unsigned i = 0 ; i < size ; i++){
        notes += walletFROM[i].number;
    }

    return notes;
}

// PRINTING
void print_fancy(unsigned arr[], unsigned size){
        unsigned valuePrev = arr[0];
        unsigned number = 0;
        for (unsigned i = 0 ; i < size ; i++){
            unsigned value = arr[i];

            if ( value == valuePrev ){
                number++;
            }
            else {
                cout << number << " x " << valuePrev << " lei\n";
                number = 1;
            }

            valuePrev = value;
        }
        cout << number << " x " << valuePrev << " lei\n\n";
}

void print(unsigned arr[], unsigned size){
    for (unsigned i = 0 ; i < size ; i++){
        cout << arr[i] << " ";
    }
    cout << "\n\n";
}

// BACKTRACKING
void backtracking_money(unsigned size, Banknote walletFROM[], unsigned walletTO[], unsigned sumToReach, unsigned sum = 0, unsigned note = 0, unsigned iter = 0){
    // STOPPING CONDITION
    if ( sum >= sumToReach ){
        // SOLLUTION CONDITION
        if ( sum == sumToReach ){
            cout << "WALLET\n";
            ( PRNT_STYLE ) ? print_fancy(walletTO, iter) : print(walletTO, iter);
        }
    }
    else {
        // ALL POSSIBILITIES
        for (unsigned index = note ; index < size ; index++){
            // VALID POSIBILITY
            if ( walletFROM[index].number != 0 ){
                unsigned value = walletFROM[index].value;

                // PUSH
                walletTO[iter] = value;
                walletFROM[index].number--;
                // BACKTRACKING()
                backtracking_money(size, walletFROM, walletTO, sumToReach, sum + value, index, iter + 1);
                // POP
                walletFROM[index].number++;
            }
        }
    }
}

int main(){
    Banknote walletFROM[] = {{5, 1}, {7, 5}, {10, 10}, {1, 100}};
    unsigned size = ( sizeof(walletFROM)/sizeof(walletFROM[0]) );
    const unsigned notes = get_notes(walletFROM, size);
    unsigned *walletTO = new unsigned[notes];

    backtracking_money(size, walletFROM, walletTO, 107);

    delete [] walletTO;
}