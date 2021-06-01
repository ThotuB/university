#include <iostream>
#include <bitset>
#include <math.h>
#include <string>

#define BITS 8
#define LVL 4

using namespace std;

class Cell {
public:
    unsigned s;
    unsigned c;

    void reset(){
        s = -1;
        c = -1;
    }

    static Cell add(bool x, bool y, bool c){
        Cell newCell;
        newCell.s = x ^ y ^ c;
        newCell.c = x&y | x&c | y&c;

        return newCell;
    }

    void copySC(Cell &newCell){
        s = newCell.s;
        c = newCell.c;
    }
    
    void copyS(Cell &newCell){
        s = newCell.s;
    }

    void print(){
        if ( c == -1 ){
            if ( s == -1 ){
                cout << "/////|";
            }
            else {
                cout << "   " << s << " |";
            }
        }
        else {
            cout << " " << c << " " << s << " |";
        }
    }
};

class Row {
public:
    Cell cell[BITS];

    void reset(){
        for (unsigned i = 0; i < BITS ; i++){
            cell[i].reset();
        }
    }

    void print(){
        cout << "|";
        for (unsigned i = 0; i < BITS ; i++){
            cell[i].print();
        }
        cout << "\n";
    }
};

class Level {
public:
    Row row[2];

    void reset(){
        row[0].reset();
        row[1].reset();
    }

    void print(){
        row[0].print();
        row[1].print();
    }
};

class Table {
public:
    Level level[LVL];

    Table(){
        for (unsigned i = 0; i < LVL ; i++){
            level[i].reset();
        }
    }

    void copy(unsigned lvl, unsigned bgn, unsigned end){
        for (unsigned i = bgn ; i <= end ; i++){
            level[lvl].row[0].cell[i].copyS(level[lvl-1].row[0].cell[i]);
            level[lvl].row[1].cell[i].copyS(level[lvl-1].row[1].cell[i]);
        }
    }
    
    void calc(unsigned lvl, unsigned bgn, unsigned end){
        for (unsigned i = bgn ; i <= end ; i++){
            level[lvl].row[0].cell[i].copySC(level[lvl-1].row[level[lvl-1].row[0].cell[end+1].c].cell[i]);
            level[lvl].row[1].cell[i].copySC(level[lvl-1].row[level[lvl-1].row[1].cell[end+1].c].cell[i]);
        }
    }

    void recur(unsigned lvl, unsigned bgn, unsigned end){
        if ( lvl > 0 ){
            unsigned mid = (bgn+end)/2;

            recur(lvl-1, mid+1, end);
            recur(lvl-1, bgn, mid);
            copy(lvl, mid+1, end);
            calc(lvl, bgn, mid);
        }
    }

    void shade(int lvl, unsigned bgn, unsigned end, bool carry){
        if ( lvl >= 0 ){
            for (unsigned i = bgn ; i <= end ; i++){
                level[lvl].row[carry].cell[i].reset();
            }
            unsigned mid = (bgn+end)/2;

            shade(lvl-1, mid+1, end, carry);
        }
    }

    void CSuA(string nr1, string nr2, bool carry){
        for (unsigned i = 0 ; i < BITS; i++){
            bool n1 = ( nr1[i] == '0' ) ? 0 : 1;
            bool n2 = ( nr2[i] == '0' ) ? 0 : 1;
            level[0].row[0].cell[i] = Cell::add(n1, n2, 0);
            level[0].row[1].cell[i] = Cell::add(n1, n2, 1);
        }

        recur(LVL-1, 0, BITS-1);
        shade(LVL-1, 0, BITS-1, !carry);
    }

    void print(){
        for (unsigned i = 0; i < LVL ; i++){
            level[i].print();
        }
    }
};

int main(){
    Table Tab;
    Tab.CSuA("0010111", "00001011", 1);
    Tab.print();
}