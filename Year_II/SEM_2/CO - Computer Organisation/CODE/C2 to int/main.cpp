#include <iostream>
#include <string>
#include <bitset>

#define pow2(x) ( 1 << x )

using namespace std;

template <size_t size>
int robertson(bitset<size> x){
    int nr = -x[size-1] * pow2(size-1);

    for (unsigned i = 0 ; i < size-1 ; i++){
        nr += x[i] * pow2(i);
    }

    return nr;
}

int main(){
    cout << robertson<4>( bitset<4>(string("0011")) ) << '\n';
}