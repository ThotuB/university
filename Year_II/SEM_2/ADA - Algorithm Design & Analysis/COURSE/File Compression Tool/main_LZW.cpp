#include <iostream>
#include <fstream>
#include <map>
#include <string>

#define PRNT 0

using namespace std;

template <class T1, class T2> void print_dict(map <T1, T2> dict, unsigned offset){
    for (auto it = next(dict.begin(), offset) ; it != dict.end() ; it++){
        cout << it->first << " - " << it->second << "\n";
    }
}

// ~~~~~~~~~~~~~~~ LZW COMPRESSION ~~~~~~~~~~~~~~~

map <string, unsigned> init_compress_dict(){
    map <string, unsigned> dictionary;

    for (unsigned i = 0 ; i < 256 ; i++){
        char c = i;
        string cStr(1, c);
        dictionary.insert(pair<string, unsigned>(cStr, i));
    }

    return dictionary;
}

void compress_LZW(ifstream& source, ofstream& dest){
    map <string, unsigned> dictionary = init_compress_dict();
    unsigned index = 256;

    string s(1, source.get());
    char c;

    while ( source.get(c) ){
        string sc = s + c;
        if (  dictionary.find(sc) != dictionary.end() ){
            s = sc;
        }
        else {
            if (PRNT) cout << dictionary[s] << "(" << s << ")\n";
            dest << dictionary[s] << " ";
            dictionary.insert(pair<string, unsigned>(sc, index++));
            s = c;
        }
    }
        
    if (PRNT) cout << dictionary[s] << "(" << s << ")\n";
    dest << dictionary[s] << " ";

    //print_dict(dictionary, 0);
}

// ~~~~~~~~~~~~~~~ LZW DECOMPRESSION ~~~~~~~~~~~~~~~

map <unsigned, string> init_decompress_dict(){
    map <unsigned, string> dictionary;

    for (unsigned i = 0 ; i < 256 ; i++){
        char c = i;
        string cStr(1, c);
        dictionary.insert(pair<unsigned, string>(i, cStr));
    }

    return dictionary;
}

void decompress_LZW(ifstream& source, ofstream& dest){
    map <unsigned, string> dictionary = init_decompress_dict();
    unsigned index = 256;

    unsigned current;
    source >> current;
    if (PRNT)cout << dictionary[current];
    dest << dictionary[current];
    unsigned previous = current;

    while ( source >> current ){
        if ( dictionary.find(current) != dictionary.end() ){
            string s = dictionary[current];
            if (PRNT) cout << s;
            dest << s;
            string prevs = dictionary[previous] + s[0];
            dictionary.insert(pair<unsigned, string>(index++, prevs));
        }
        else {
            string s = dictionary[previous] + dictionary[previous][0];
            if (PRNT) cout << s;
            dest << s;
            dictionary.insert(pair<unsigned, string>(index++, s));
        }
        previous = current;
    }

    print_dict(dictionary, 256);
}

int main(int argc, char **argv){
    if ( argc != 4 ){
        cerr << "USAGE: " << argv[0] << " mode inputfile outputfile\n";
        exit(1);
    }

    ifstream file_in(argv[2]);
    ofstream file_out(argv[3]);

    if ( !file_in || !file_out ){
        cerr << "FILE OPENING ERROR\n";
        exit(2);
    }

    if ( string(argv[1]) == "-c" ){
        compress_LZW(file_in, file_out);
    }
    else if ( string(argv[1]) == "-d" ){
        decompress_LZW(file_in, file_out);
    }
    else {
        cerr << "MODE ERROR\n";
        exit(3);
    }

    file_in.close();
    file_out.close();

    return 0;
}