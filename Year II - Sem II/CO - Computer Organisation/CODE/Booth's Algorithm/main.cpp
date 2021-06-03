#include <iostream>
#include <string>
#include <bitset>

#define pow2(x) ( 1 << (x) )

using namespace std;

template <size_t S1, size_t S2 >
bitset <S1 + S2> concat( const bitset <S1> & b1, const bitset <S2> & b2 ) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset <S1 + S2>( s1 + s2 );
}

template <size_t size>
int booth(bitset<size> x, unsigned Y){
    bitset<size+1> X = concat(x, bitset<1>(0));

    int nr = 0;
    for (unsigned i = 1 ; i < size+1 ; i++){
        nr += (X[i-1] - X[i]) * pow2(i-1) * Y;
        cout << X[i-1] << X[i] << " - " << nr << "\n";
    }

    return nr;
}

int main(){
    cout << booth<4>( bitset<4>(string("1011")), 3) << '\n';
}