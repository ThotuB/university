#include <iostream>

template<size_t BITS>
class Bits {
public:
    bool bit[BITS] = {0};

    Bits(){}

    Bits(unsigned nr){
        for (unsigned i = 0 ; i < BITS ; i++){
            bit[i] = ( nr >> i ) & 0x1;
        }
    }

    // Bits(Bits& copyBits){
    //     for (unsigned i = 0 ; i < BITS ; i++){
    //         bit[i] = ( nr >> i ) & 0x1;
    //     }
    // }

    // BIT SHIFTING
    void LSH(bool lsb){
        for (unsigned i = BITS-1; i > 0 ; i--){
            bit[i] = bit[i-1];
        }
        bit[0] = lsb;
    }

    void RSH(bool msb){
        for (unsigned i = 0; i < BITS-1 ; i++){
            bit[i] = bit[i+1];
        }
        bit[BITS-1] = msb;
    }

    void ARSH(){
        for (unsigned i = 0; i < BITS-1 ; i++){
            bit[i] = bit[i+1];
        }
        bit[BITS-1] = bit[BITS-2];
    }
    
    // MIN/MAX
    static Bits<BITS> max(Bits nr1, Bits nr2){
        if ( nr1.to_uint() > nr2.to_uint() ){
            return nr1;
        }
        return nr2;
    }


    // TO (UN)SIGNED INTEGER
    unsigned to_uint(){
        unsigned nr = 0;
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( bit[BITS-i-1] ) ? 1 : 0;
            nr <<= 1;
            nr += b;
        }
        return nr;
    }

    unsigned to_int(){
        unsigned nr = 0;
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( bit[BITS-i-1] ) ? 1 : 0;
            nr <<= 1;
            nr += b;
        }
        return nr;
    }
    
    // ARITHMETIC OPERATORS
    Bits operator+(Bits addBits){
        return Bits(this->to_uint() + addBits.to_uint());
    }

    Bits operator-(Bits subBits){
        return Bits(this->to_uint() - subBits.to_uint());
    }

    Bits& operator+=(unsigned nr){
        *this = Bits(this->to_uint() + nr);
        return *this;
    }

    Bits& operator-=(unsigned nr){
        *this = Bits(this->to_uint() - nr);
        return *this;
    }

    // ADDRESS OPERATOR
    bool &operator[](unsigned index) {
        return bit[index];
    }

    // LOGIC OPERATORS
    bool operator==(int nr){
        return ( this->to_int() == nr );
    }
    
    bool operator<(int nr){
        return ( this->to_int() < nr );
    }
    
    bool operator>(int nr){
        return ( this->to_int() > nr );
    }

    // PRINT OPERATOR
    friend std::ostream& operator<<(std::ostream& out, Bits outBits){
        for (unsigned i = 0 ; i < BITS ; i++){
            out << outBits.bit[BITS-i-1];
        }
        //out << " " << outBits.to_uint();
        return out;
    }
};