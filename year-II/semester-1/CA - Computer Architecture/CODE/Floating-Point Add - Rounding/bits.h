#include <iostream>
#include <string>

template <size_t E, size_t M>
class Bits {
public:
    bool sgn;
    bool exp[E];
    bool man[M];

    Bits(std::string nr){
        sgn = nr[0] - '0';
        for (unsigned i = 0 ; i < E ; i++){
            exp[i] = nr[i+1] - '0';
        }
        for (unsigned i = 0 ; i < M ; i++){
            man[i] = nr[i+E+1] - '0';
        }
    }

    void print(){
        std::cout << sgn << "|";
        for (unsigned i = 0 ; i < E ; i++){
            std::cout << exp[i];  
        }
        std::cout << "|";
        for (unsigned i = 0 ; i < M ; i++){
            std::cout << man[i];
        }
        std::cout << "\n";
    }
};