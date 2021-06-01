#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

#define pin_t pair <int, Node*>

class Node {
public:
    int nr;
    char c;
    Node* left;
    Node* right;

    Node(unsigned _nr, char _c){
        nr = _nr;
        c = _c;
        left = NULL;
        right = NULL;
    }

    Node(unsigned _nr, Node* _left, Node* _right){
        nr = _nr;
        c = '\0';
        left = _left;
        right = _right;
    }

    void print_node(){
        cout << "Node: " << this << "\n";
        cout << " -nr: " << nr << "\n";
        if ( c != '\0' ) cout << " -c: " << (int)c << "\n";
        cout << " *left: " << left << "  *right: " << right << "\n";
    }

    void print_preorder(){
        print_node();
        if ( left != NULL ) left->print_preorder();
        if ( right != NULL ) right->print_preorder();
    }
};

void print_queue(const priority_queue <pin_t, vector<pin_t>, greater<pin_t>> &Q){
    priority_queue <pin_t, vector<pin_t>, greater<pin_t>> cpyQ = Q;

    while ( !cpyQ.empty() ){
        cout << cpyQ.top().first << " - " << cpyQ.top().second->c << "\n";
        cpyQ.pop();
    }
}

Node* build_huffman_tree(map <char, int> data){
    priority_queue <pin_t, vector<pin_t>, greater<pin_t>> Q;

    for (auto& it : data){
        Q.push( pair<int, Node*>( it.second, new Node(it.second, it.first) ) );
    }

    print_queue(Q);

    for (unsigned i = 0 ; i < data.size() - 1 ; i++){
        Node* x = Q.top().second; Q.pop();
        Node* y = Q.top().second; Q.pop();

        Node* z = new Node(x->nr + y->nr, x, y);

        Q.push( pair<int, Node*>(z->nr, z) );
    }

    return Q.top().second;
}

map < char, int > get_chars(ifstream &fin){
    map < char, int > data;

    char c;
    while ( fin.get(c) ){
        data[c]++;
    }

    return data;    
}

int main(){
    ifstream file_in("data_raw.txt");
    map <char, int> data = get_chars(file_in);

    Node* huffTree = build_huffman_tree(data);

    huffTree->print_preorder();
}