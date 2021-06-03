#include <iostream>
#include <string>

template<size_t BITS>
class Bits {
public:
    bool bit[BITS] = {0};

    Bits(){}

    Bits(std::string nr){
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( nr[i] == '0' ) ? 0 : 1;
            bit[i] = b;
        }
    }

    Bits(unsigned nr){
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( nr >> i ) & 0x1;
            bit[BITS-i-1] = b;
        }
    }

    Bits(int nr, int exp, bool isInt){
        if ( isInt ){
            for (int i = exp ; i > 0 ; i--){
                nr*=2;
            }
        }
        else {
            for (int i = exp ; i > -BITS+1 ; i--){
                nr*=2;
            }
        }
        bool sgn = ( nr < 0 ) ? 1 : 0;
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( nr >> i ) & 0x1;
            bit[BITS-i-1] = b;
        }
        bit[0] = sgn;
    }

    void RSH(bool msb){
        for (unsigned i = BITS-1; i > 0 ; i--){
            bit[i] = bit[i-1];
        }
        bit[0] = msb;
    }

    unsigned to_uint(){
        unsigned nr = 0;
        for (unsigned i = 0 ; i < BITS ; i++){
            bool b = ( bit[i] ) ? 1 : 0;
            nr <<= 1;
            nr += b;
        }
        return nr;
    }
    
    Bits& operator+=(Bits& addBits){
      Bits sum(this->to_uint() + addBits.to_uint());
      *this = sum;
      return *this;
    }

    Bits& operator-=(Bits& addBits){
      Bits sum(this->to_uint() - addBits.to_uint());
      *this = sum;
      return *this;
    }

    Bits& operator+=(unsigned nr){
      Bits sum(this->to_uint() + nr);
      *this = sum;
      return *this;
    }

    bool &operator[](unsigned index) {
        return bit[BITS-index-1];
    }

    friend bool operator==(Bits &nr1, unsigned nr2){
        return (nr1.to_uint() == nr2);
    }


    friend std::ostream& operator<<(std::ostream& out, const Bits& outBits){
        for (unsigned i = 0 ; i < BITS ; i++){
            out << outBits.bit[i];
        }
        return out;
    }
};