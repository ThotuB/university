#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

string read(FILE* stream){
    string text;

    for (char c = fgetc(stream) ; c != EOF ; c = fgetc(stream)){
        text.push_back(c);
    }

    return text;
}

map <char, int> get_displacement_arr(string text){
    map <char, int> displacement;
    unsigned len = text.length();

    for (int i = len - 2 ; i >= 0 ; i--){
        if ( displacement.find(text[i]) == displacement.end() ){
            displacement.insert( pair <char, int>(text[i], len - i - 1) );
        }
    }

    return displacement;
}

void print_map(map <char, int> Map, unsigned len){
    for (auto it = Map.cbegin() ; it != Map.cend() ; it++){
        cout << it->first << " - " << it->second << "\n";
    }
    cout << "* - " << len << "\n\n";
}

void write(string source, vector<unsigned> found, unsigned modelLen){
    unsigned len = source.length();
    unsigned index = 0;

    for (unsigned i = 0 ; i < len ; i++){
        if ( i == found[index] ){
            cout << "\033[0;31m";
            for (unsigned j = 0 ; j < modelLen ; j++){
                cout << source[i];
                i++;
            }
            cout << "\033[0m";
            index++;
        }
        else {
            cout << source[i];
        }
    }
}

vector<unsigned> Boyer_Moore(string model, string source){
    vector<unsigned> findPos;

    map <char, int> displacement = get_displacement_arr(model);

    cout << source << "\n" << model << "\n\n";
    print_map(displacement, model.length());

    unsigned sourceLen = source.length();
    unsigned modelLen = model.length();
    unsigned modelPosEnd = modelLen;

    unsigned step = 1;

    while ( modelPosEnd <= sourceLen ){
        cout << "Step "<< step << ": ";

        if ( source.compare(modelPosEnd - modelLen, modelLen, model) ){
            if ( displacement.find(source[modelPosEnd-1]) != displacement.end() ){
                cout << displacement[source[modelPosEnd-1]] << "\n";

                modelPosEnd += displacement[source[modelPosEnd-1]];
            }
            else {
                cout << modelLen << "\n";

                modelPosEnd += modelLen;
            }
        }
        else {
            cout << "Found - " << modelPosEnd - modelLen <<"\n";
            findPos.push_back(modelPosEnd - modelLen);
            modelPosEnd++;
        }
        step++;
    }

    return findPos;
}

int main(){
    FILE* sourceFile = fopen("../source.txt", "r");
    FILE* modelFile = fopen("../model.txt", "r");

    string source = read(sourceFile);
    string model = read(modelFile);

    vector<unsigned> indexes;

    indexes = Boyer_Moore(model, source);

    write(source, indexes, model.length());

    return 0;
}
