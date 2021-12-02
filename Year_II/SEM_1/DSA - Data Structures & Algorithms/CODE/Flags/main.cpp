#include <iostream>

using namespace std;

void print_array(char *Arr, unsigned size){
    for (unsigned i = 0 ; i < size ; i++){
        cout << Arr[i];
    }
    cout << "\n";
}

bool valid(char flag[]){
    if ( flag[0] != flag[1] && flag[1] != flag[2] && flag[2] != flag[0] ){
        if ( flag[1] == 'y' || flag[1] == 'g' ){
            return true;
        }
    }
    return false;
}

void build_flag(char colors[], unsigned size, unsigned step=0){
    static char flag[3];
    if ( step == 3 ){
        if ( valid(flag) )
            print_array(flag, 3);
    }
    else {
        for (unsigned i = 0 ; i < size ; i++){
            flag[step] = colors[i];
            //cout << colors[i];
            build_flag(colors, size, step+1);
        }
    }
}

int main(){
    char colors[] = {'w', 'y', 'r', 'g', 'b', 'B'};

    build_flag(colors, 6);
}