#include <iostream>
#include <string>
#include <fstream>

#include "../../lib/token.hpp"
#include "../../lib/lexical_analyzer.hpp"

using namespace std;
using namespace atom_c_compiler;

int main() {
    // read file into string
    std::ifstream file("../../res/input.c");

    int length;
    file.seekg(0, std::ios::end);
    length = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char *buffer = new char[length];
    file.read(buffer, length);

    std::string str(buffer);

    cout << str << endl;
    
    // lexical analysis
    vector<Token> tokens = Lexical_Analyzer::tokenize(str);

    for (Token token : tokens) {
        token.print();
    }

    return 0;
}