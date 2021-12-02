#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

#define T 3
#define llu long long unsigned

class Data {
public:
    string key;
    llu value;

    Data(string _key, llu _value){
        key = _key;
        value = _value;
    }
};

class Node {
public:
    Node *root = NULL;

    unsigned dataSize = 0;
    vector < Data > data;

    unsigned cSize = 0;
    vector <Node*> c;

    bool leaf;

public:
    Node(){
        leaf = true;
    }

    Node(Node* nodeToSplit, Node* newRoot, bool flagLeftRight){
        leaf = true;
        if ( !flagLeftRight ){  // LEFT
            // Data
            data.insert(data.begin(), nodeToSplit->data.begin(), nodeToSplit->data.end() - T);
            dataSize = data.size();
            // Nodes
            if ( !nodeToSplit->leaf ){
                c.insert(c.begin(), nodeToSplit->c.begin(), nodeToSplit->c.end() - T);
                cSize = c.size();
                for (unsigned i = 0 ; i < cSize ; i++){
                    c[i]->root = this;
                }
                leaf = false;
            }
        }
        else {  // RIGHT
            // Data
            data.insert(data.begin(), nodeToSplit->data.begin() + T, nodeToSplit->data.end());
            dataSize = data.size();
            // Nodes
            if ( !nodeToSplit->leaf ){
                c.insert(c.begin(), nodeToSplit->c.begin() + T, nodeToSplit->c.end());
                cSize = c.size();
                for (unsigned i = 0 ; i < cSize ; i++){
                    c[i]->root = this;
                }
                leaf = false;
            }
        }

        root = newRoot;
    }

    void root_split(){
        Node* left = new Node(this, this, 0);
        Node* right = new Node(this, this, 1);
    
        // Data
        Data midData = data[T-1];
        data.clear();
        data.push_back(midData);
        dataSize = 1;
        // Nodes
        c.clear();
        c.push_back(left);
        c.push_back(right);
        cSize = 2;

        leaf = false;
    }

    void normal_split(){
        Node* left = new Node(this, root, 0);
        Node* right = new Node(this, root, 1);
    
        Data  midData = data[T-1];
        unsigned i;
        for (i = 0 ; i < root->dataSize ; i++){
            if ( midData.key.compare(root->data[i].key) < 0 ){
                break;
            }
        }
        // Data
        root->data.insert(root->data.begin() + i, midData);
        root->dataSize++;
        // Nodes
        root->c[i] = left;
        root->c.insert(root->c.begin() + i + 1, right);
        root->cSize++;
    }

    void insert(Data dataToInsert){
        if ( dataSize == 2*T-1 ){
            if ( root == NULL ){
                this->root_split();
            }
            else {
                this->normal_split();
                this->root->insert(dataToInsert);
                return;
            }
        }

        unsigned i;// = upper_bound(key.begin(), key.end(), keyToInsert) - key.begin();
        for (i = 0 ; i < dataSize ; i++){
            if ( dataToInsert.key.compare(data[i].key) < 0 ){
                break;
            }
        }
        if ( !leaf ){
            c[i]->insert(dataToInsert);
        }
        else {
            data.insert(data.begin() + i, dataToInsert);
            dataSize++;
        }
    }

    void insert(string keyToInsert, llu valueToInsert){
        insert(Data(keyToInsert, valueToInsert));
    }

    void print(){
        for (unsigned i = 0 ; i < dataSize ; i++){
            cout << data[i].key << "(" << data[i].value << ") ";
        }
        cout << '\n';
        for (unsigned i = 0 ; i < cSize ; i++){
            c[i]->print();
        }
    }

    void print_details(){
        cout << root << " - " << this << ( (leaf) ? " (leaf)" : " (node)" ) << ": ";
        for (unsigned i = 0 ; i < data.size() ; i++){
            cout << data[i].key << "(" << data[i].value << ") ";
        }
        cout << '\n';
        for (unsigned i = 0 ; i < c.size() ; i++){
            cout << c[i] << " ";
        }
        cout << ( (leaf) ? '\0' : '\n' );
        for (unsigned i = 0 ; i < c.size() ; i++){
            c[i]->print_details();
        }
    }

    void print_levels_actual(queue <Node*> nodeQ, unsigned level){
        queue <Node*> newNodeQ;
        cout << level << ": ";
        while ( !nodeQ.empty() ){
            Node* node = nodeQ.front();
            for (unsigned i = 0 ; i < node->dataSize ; i++){
                cout << node->data[i].key << " " ;//<< "(" << node->data[i].value << ") ";
                if ( !node->leaf ){
                    newNodeQ.push(node->c[i]);
                }
            }
            cout << "  ";
            if ( !node->leaf ){
                newNodeQ.push(node->c[node->dataSize]);
            }
            nodeQ.pop();
        }
        cout << '\n';
        if ( !newNodeQ.empty() ){
            print_levels_actual(newNodeQ, level+1);
        }
    }

    void print_levels(){
        queue <Node*> q;
        q.push(this);
        print_levels_actual(q, 1);
    }
};

class Index {
private:
    ifstream datafile;
    fstream indexfile;
    Node* root = new Node();

public:
    Index(string datafileName, unsigned recordSize, unsigned keySize){
        datafile.open(datafileName);

        char* buffer = new char[recordSize];

        llu val = 0;

        while ( datafile.read(buffer, recordSize) ){
            string strBuf(buffer, recordSize);
            root->insert(strBuf.substr(0, keySize), val);

            val += recordSize;
        }

        root->print_levels();
    }

};

int main(){
    Index myIndex("test.dat", 84, 4);

}