#include <iostream>
#include <math.h>

#define bits *1
#define bytes *8

#define GiB *pow(2, 30)
#define MiB *pow(2, 20)
#define KiB *pow(2, 10)

using namespace std;

typedef double var;

enum Units { BYTE, WORD };

var main_memory_size = 32 GiB;
Units addressable_unit = BYTE;
var word_size = 64 bits;
var block_size = 8;

var cache_sets = 8;
var cache_data_size = 128 KiB;

void print_address(var tag, var index, var blockOff, var wordOff){
    var address[] = {tag, index, blockOff, wordOff};
    cout << "address: " << tag + index + blockOff + wordOff << "\n";
    for (unsigned i = 0 ; i < 4 ; i++){
        for (unsigned j = 0 ; j < address[i] ; j++){
            cout << (char)219;
        }
        cout << "|";
    }
    cout << "\ntag: " << tag 
        << "\nindex: " << index
        << "\nblock offset: " << blockOff;
    switch ( addressable_unit ){
        case BYTE:
            cout << "\nbyte";
            break;
        case WORD:
            cout << "\nword";
            break;
    }
    cout << " offset: " << wordOff << "\n";
}

int main(){
    var addressSize = log2(main_memory_size);
    var wordOffset = log2(word_size/8);
    var blockOffset = log2(block_size);
    var cacheSizeExp = log2(cache_data_size);

    var blocksPerCache = cacheSizeExp - (blockOffset + wordOffset);
    var index = blocksPerCache - log2(cache_sets);

    var tag = addressSize - (index + blockOffset + wordOffset);

    print_address(tag, index, blockOffset, wordOffset);

    return 0;
}