#include <iostream>
#include <vector>
#include <string>

using namespace std;

class node {
public:
    char elem;
    vector <struct node*> letters;
    bool end;

    node(char _elem, bool _end){
        elem = _elem;
        letters.clear();
        end = _end;
    }
    
    void insert(node* _node){
        letters.push_back(_node);
    }
    
    node* insert_letter(char _elem, bool _end){
        for (node* &_node : letters){
            if ( _node->elem == _elem ){
                end = ( end ) ? true : _end;
                return _node;
            }
        }
        node* newNode = new node(_elem, _end);
        this->insert(newNode);

        return newNode;
    }

    void insert_word(string word){
        node* curr = this;

        unsigned wordLen = word.size();
        for (unsigned i = 0 ; i < wordLen ; i++){
            bool end = ( i == wordLen-1 );
            curr = curr->insert_letter(word[i], end);
        }
    }

    void print(){
        for (node* _node : letters){
            cout << elem << "-" << _node->elem << '\n';
            _node->print();
        }
    }

    void print_all(string word = ""){
        if ( end ){
            cout << word << "\n";
        }
        for (node* _node : letters){
            _node->print_all(word + _node->elem);
        }
    }
};

#define Node node*

int main(){
    Node root = new node('*', false);

    string wordArr[] = {
        "rocks",
        "rocky",
        "rocked",
        "rocker",
        "rocket",
        "rockaby",
        "rockers",
        "rockery",
        "rockets",
        "rockier",
        "rockies",
        "rocking",
        "rockabye",
        "rocketed",
        "rocketer",
        "rocketry",
        "rockfall",
        "rockfish",
        "rockiest",
        "rockless",
        "rocklike",
        "rockabies",
        "rockabyes",
        "rockaways",
        "rockeries",
        "rocketers",
        "rocketing",
        "rockfalls",
        "rockiness",
        "rockroses",
        "rockworks",
        "rocketlike",
        "rocketries",
        "rockfishes"
    };

    unsigned size = (sizeof(wordArr)/sizeof(wordArr[0]));
    for (unsigned i = 0 ; i < size ; i++){
        root->insert_word(wordArr[i]);
    }

    root->print_all();
}