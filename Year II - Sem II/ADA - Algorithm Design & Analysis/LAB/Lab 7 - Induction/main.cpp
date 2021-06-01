#include <iostream>
#include <stack>

using namespace std;

#define SIZE 4

int celebrity_solution(bool knows[SIZE][SIZE], unsigned size){
    stack <unsigned> Stack;

    for (unsigned i = 0 ; i < size ; i++){
        Stack.push(i);
    }

    while ( Stack.size() > 1 ){
        unsigned stays;

        unsigned i = Stack.top();
        Stack.pop();
        unsigned j = Stack.top();
        Stack.pop();

        if ( knows[i][j] ){
            stays = j;
        }
        else {
            stays = i;
        }

        Stack.push(stays);
    }

    unsigned p = Stack.top();
    Stack.pop();

    for (unsigned i = 0 ; i < size ; i++){
        if ( ( knows[p][i] || !knows[i][p] ) && ( i != p ) ){
            return -1;
        }
    }
    return p;
}

int main(){
    bool knows[SIZE][SIZE] = {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}};;

    cout << "Celebrity: " << celebrity_solution(knows, SIZE) << "\n";

    return 0;
}