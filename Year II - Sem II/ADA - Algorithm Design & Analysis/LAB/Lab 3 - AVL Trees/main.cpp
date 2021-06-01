#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

class node {
public:
    int key;
    node* left;
    node* right;
    node *p;
    int height;
};

typedef struct node* Node;

Node newNode(int key) {
    Node node = (Node) malloc(sizeof(struct node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    node->height = 1;

    return (node);
}

void InsertBST(Node* root, int key) {
    Node z = newNode(key);
    Node prev, curr;

    prev = NULL;
    curr = *root;
    while ( curr != NULL) {
        prev = curr;
        if ( curr->key < z->key ){
            curr = curr->right;
        }
        else{
            curr = curr->left;
        }
    }
    z->p = prev;
    if ( prev == NULL ) {
        *root = z;
    }
    else {
        if (z->key <= prev->key){
            prev->left = z;
        }
        else{
            prev->right = z;
        }
    }

}

int HeightAVL(Node root){
    if ( root != NULL ){
        return root->height;
    }
    return 0;
}

Node LeftRotate(Node x){
    Node y = x->right;
    x->right = y->left;

    if ( y->left != NULL ){
        y->left->p = x;
    }
    y->p = x->p;

    if ( x->p != NULL ){
        if ( x == x->p->left ){
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
    }

    y->left = x;
    x->p = y;

    x->height = max(HeightAVL(x->left), HeightAVL(x->right)) + 1;
    y->height = max(HeightAVL(y->left), HeightAVL(y->right)) + 1;

    return y;
}

Node RightRotate(Node y){
    Node x = y->left;
    y->left = x->right;

    if ( x->right != NULL ){
        x->right->p = y;
    }
    x->p = y->p;

    if ( y->p != NULL ){
        if ( y == y->p->right ){
            y->p->right = x;
        }
        else {
            y->p->left = x;
        }
    }

    x->right = y;
    y->p = x;

    x->height = max(HeightAVL(x->left), HeightAVL(x->right)) + 1;
    y->height = max(HeightAVL(y->left), HeightAVL(y->right)) + 1;

    return x;
}

Node Balance(Node x){
    if ( abs( HeightAVL(x->left) - HeightAVL(x->right) ) <= 1 ){
        return x;
    }
    else if ( HeightAVL(x->left) > HeightAVL(x->right) ){
        Node y = x->left;
        if ( HeightAVL(y->left) < HeightAVL(y->right) ){
            LeftRotate(y);
        }
        
        return RightRotate(x);
    }
    else {
        Node y = x->right;
        if ( HeightAVL(y->left) > HeightAVL(y->right) ){
            RightRotate(y);
        }
            
        return LeftRotate(x);
    }
}

Node InsertAVL(Node &x, Node z){
    if ( x == NULL ) {
        z->height = 1;
        return z;
    }

    if (z -> key <= x -> key) {
        Node y = InsertAVL(x->left, z);

        x->left = y;
        y->p = x;
        x->height = y->height + 1;
    }

    else {
        Node y = InsertAVL(x->right, z);

        x->right = y;
        y->p = x;
        x->height = y->height + 1;
    }

    x = Balance(x);

    x->height = max(HeightAVL(x->left), HeightAVL(x->right)) + 1;

    return x;
}

// TREE TRAVERSAL
void Preorder(Node root) {
    if ( root != NULL ){
        cout << root->key << " " << root->height << "\n";
        Preorder(root->left);
        Preorder(root->right);
    }
}

void Inorder(Node root) {
    if ( root != NULL ){
        Inorder(root->left);
        cout << root->key << " ";
        Inorder(root->right);
    }
}

void Postorder(Node root) {
    if ( root != NULL ){
        Postorder(root->left);
        Postorder(root->right);
        cout << root->key << " ";
    }
}

int HeightBST(Node root){
    int height = 0;
    int nodes = 1;
    
    queue<Node> q;

    q.push(root);

    while ( !q.empty() ) {
        Node parent = q.front();
        q.pop();
        nodes--;

        if ( parent->left != NULL )
            q.push(parent->left);

        if ( parent->right != NULL )
            q.push(parent->right);
        
        if ( nodes == 0 ) {
            height++;
            nodes = q.size();
        }
    }

    return height;
}


void PrintLevels(Node root){
    queue<Node> q;

    q.push(root);

    while ( !q.empty() ){
        Node parent = q.front();

        cout << parent->key << " ";

        if ( parent->left != NULL ){
            q.push(parent->left);
        }
        if ( parent->right != NULL ){
            q.push(parent->right);
        }

        q.pop();
    }
}

int main(){
    clock_t timeStart, timeStop;
    srand(time(NULL));

    Node treeBST = NULL;

    timeStart = clock();
    for (unsigned i = 0 ; i < 1000000 ; i++){
        InsertBST(&treeBST, i);
    }
    timeStop = clock();

    cout << ((double) (timeStop - timeStart)) * 1000 / CLOCKS_PER_SEC << '\n';

    timeStart = clock();
    cout << "HEIGHT - BST: " << HeightBST(treeBST) << '\n';
    timeStop = clock();
 
    cout << ((double) (timeStop - timeStart)) * 1000 / CLOCKS_PER_SEC << '\n';

    Node treeAVL = NULL;
    // timeStart = clock();
    // for (unsigned i = 0 ; i < 1000000 ; i++){
    //     treeAVL = InsertAVL(treeAVL, newNode(rand()) );
    // }
    // timeStop = clock();
    
    // cout << ((double) (timeStop - timeStart)) * 1000 / CLOCKS_PER_SEC << '\n';

    // cout << "Height - AVL: " << HeightAVL(treeAVL) << '\n';

    //Preorder(treeAVL);
}

///                         BINARY SEARCH TREE
///                 Height          Height (Time)           Insertion (Time)
/// RANDOM:         83              114ms                   1,554ms
/// ORDERED:        1 mil           73ms                    4,380,750ms ~ 1 hour

///                             AVL TREE - 1 mil
///                 Height          Height (Time)           Insertion (Time)
/// RANDOM:         23              0 (instant calc.)       1,209ms
/// ORDERED:        20              0 (instant calc.)       623ms