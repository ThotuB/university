#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/lexical_analyzer.hpp"
#include "../../lib/syntactical_analyzer.hpp"
#include "../../lib/token.hpp"

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

    // for (auto &token : tokens) {
    //     cout << token.code << endl;
    // }

    // syntactical analysis
    Syntactical_Analyzer analyzer = Syntactical_Analyzer(tokens);
    analyzer.analyze();

    return 0;
}