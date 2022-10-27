#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Banknote {
private:
    unsigned _number;
    unsigned _value;

public:
    // CONSTRUCTORS
    Banknote() {}

    Banknote(unsigned number, unsigned value):
        _number(number),
        _value(value)
    {}

    Banknote(unsigned value):
        Banknote(1, value)
    {}

    // GETTER
    unsigned number(){
        return _number;
    }

    unsigned value(){
        return _value;
    }

    // OPERATORS
    friend Banknote operator+=(Banknote &THIS, unsigned number){
        THIS._number += number;
        return THIS;
    }

    friend Banknote operator-=(Banknote &THIS, unsigned number){
        THIS._number -= number;
        return THIS;
    }

    friend Banknote operator++(Banknote &THIS, int){
        THIS._number++;
        return THIS;
    }

    friend Banknote operator--(Banknote &THIS, int){
        THIS._number--;
        return THIS;
    }

    friend bool operator==(Banknote &a, Banknote &b){
        return ( a._value == b._value ) ;
    }

    friend ostream& operator<<(ostream& out, const Banknote& THIS){
        out << THIS._number << " x " << THIS._value << " lei";

        return out;
    }
};

class Wallet {
private:
    unsigned _size;
    vector <Banknote> notes;

public:
    // CONSTRUCTOR
    Wallet():
        _size(0)
    {}

    // GETTER
    unsigned size(){
        return _size;
    }

    // ADDING BANKNOTE
    void push(Banknote newBanknote){
        for (unsigned i = 0 ; i < _size ; i++){
            if ( notes[i] == newBanknote ){
                notes[i] += newBanknote.number();
                return;
            }
        }
        
        notes.push_back(newBanknote);
        _size++;
    }

    // PUSH & POP
    void push(unsigned value){
        push(Banknote(value));
    }

    void pop(){
        if ( _size == 0 ){
            exit(0);
        }

        notes[_size-1]--;
        if ( notes[_size-1].number() == 0 ){
            notes.pop_back();
            _size--;
        }
    }

    // OPERATORS
    Banknote& operator[](size_t index){
        if ( index >= _size ){
            cerr << "ERROR: INVALID INDEX";
            exit(0);
        }

        return notes[index];
    }

    friend ostream& operator<<(ostream& out, const Wallet& THIS){
        out << "WALLET\n";
        for (unsigned i = 0 ; i < THIS._size ; i++){
            out << THIS.notes[i] << "\n";
        }
        out << "\b\b\n";

        return out;
    }
};

void backtracking_money1(Wallet walletFROM, unsigned sumToReach, unsigned note = 0, unsigned sum = 0, Wallet walletTO = Wallet()){
    // STOPPING CONDITION
    if ( sum >= sumToReach ){
        // SOLLUTION CONDITION
        if ( sum == sumToReach ){
            // WALLET PRINTING
            cout << walletTO;
        }
    }
    else {
        // ALL POSSIBILITIES
        for (unsigned index = note ; index < walletFROM.size() ; index++){
            // VALID POSIBILITY
            if ( walletFROM[index].number() != 0 ){
                unsigned value = walletFROM[index].value();

                // PUSH
                walletTO.push(value);
                walletFROM[index]--;
                // BACKTRACKING()
                backtracking_money1(walletFROM, sumToReach, index, sum + value, walletTO);
                // POP
                walletFROM[index]++;
                walletTO.pop();
            }
        }
    }
}

void backtracking_money2(Wallet walletFROM, unsigned sumToReach, unsigned note = 0, unsigned sum = 0, stack <unsigned> walletTO = stack <unsigned>()){
    // STOPPING CONDITION
    if ( sum >= sumToReach ){
        // SOLLUTION CONDITION
        if ( sum == sumToReach ){
            // FANCY STACK PRINTING
            cout << "WALLET\n";
            while ( !walletTO.empty() ){
                cout << walletTO.top() << " ";
                walletTO.pop();
            }
            cout << "\n\n";
        }
    }
    else {
        // ALL POSSIBILITIES
        for (unsigned index = note ; index < walletFROM.size() ; index++){
            // VALID POSIBILITY
            if ( walletFROM[index].number() != 0 ){
                unsigned value = walletFROM[index].value();

                // PUSH
                walletTO.push(value);
                walletFROM[index]--;
                // BACKTRACKING()
                backtracking_money2(walletFROM, sumToReach, index, sum + value, walletTO);
                // POP
                walletFROM[index]++;
                walletTO.pop();
            }
        }
    }
}

int main(){
    Wallet myWallet;

    myWallet.push(Banknote(5, 1));
    myWallet.push(Banknote(7, 5));
    myWallet.push(Banknote(10, 10));
    myWallet.push(Banknote(100));

    cout << "~~~ METHOD I ~~~\n";
    backtracking_money1(myWallet, 107);
    cout << "~~~ METHOD II ~~~\n";
    backtracking_money2(myWallet, 107);
}