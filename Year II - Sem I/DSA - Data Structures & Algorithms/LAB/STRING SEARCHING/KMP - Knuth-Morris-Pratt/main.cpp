#include <iostream>
#include <map>
#include <string>
#include <vector>

#define SHOW_STEPS 1;

using namespace std;

string read(FILE* stream){
    string text;

    for (char c = fgetc(stream) ; c != EOF ; c = fgetc(stream)){
        text.push_back(c);
    }

    return text;
}

map <string, int> get_displacement_arr(string text){
    map <string, int> displacement;
    unsigned len = text.length();

    for (int i = 0 ; i < len ; i++){
        string match = text.substr(0,i);    // Matrching Substring - text(0, x)
        unsigned matchLen = match.length();

        char charAfterMatch = text[i];      // Character after Match
        unsigned disp = matchLen + 1;

        for (int j = matchLen - 1 ; j >= 0 ; j--){
            string prefix = match.substr(0, j);     // Prefix - match(0, y)
            string suffix = match.substr(matchLen - j, matchLen);   // Suffix - match(len - y, len)

            if ( prefix.compare(suffix) == 0 ) {    // Checking Prefix == Suffix
                char charAfterPrefix = text[j];     // Character after Prefix

                if ( charAfterPrefix != charAfterMatch ){   // Checking CAP != CAM
                    disp = matchLen - j;
                    break;
                }
            }
        }
        displacement.insert( pair <string, int>(match, disp) );
    }

    return displacement;
}

void print_map(map <string, int> Map){
    for (auto it = Map.cbegin() ; it != Map.cend() ; it++){
        cout << it->first << " - " << it->second << "\n";
    }
    cout << "\n";
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

vector<unsigned> Knuth_Morris_Pratt(string model, string source){
    vector<unsigned> findPos;

    map <string, int> displacement = get_displacement_arr(model);

    cout << source << "\n" << model << "\n\n";
    print_map(displacement);

    unsigned sourceLen = source.length();
    unsigned modelLen = model.length();
    unsigned modelPosBegin = 0;

    unsigned step = 1;

    while ( modelPosBegin + modelLen <= sourceLen ){
        cout << "Step "<< step << ": "; 
        
        int index = -1;
        for (unsigned i = 0 ; i < modelLen ; i++){
            if ( model[i] !=  source[modelPosBegin + i]){
                index = i;
                break;
            }
        }

        if ( index == -1 ){
            cout << "Found - " << modelPosBegin << "\n";
            findPos.push_back(modelPosBegin);
            modelPosBegin++;
        }
        else {
            cout << displacement[model.substr(0, index)] << "\n";
            modelPosBegin += displacement[model.substr(0, index)];
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

    indexes = Knuth_Morris_Pratt(model, source);

    write(source, indexes, model.length());

    return 0;
}