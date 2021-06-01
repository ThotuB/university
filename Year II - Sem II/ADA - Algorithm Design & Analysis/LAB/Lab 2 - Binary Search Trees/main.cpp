#include <iostream>
#include <stdlib.h>
#include <cstdarg>
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
};

typedef struct node* Node;

Node newNode(int key) {
    Node node = (Node) malloc(sizeof(struct node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;

    return(node);
}

void Insert(Node* root, int key) {
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

void InsertArr(Node *root, unsigned size, int *Keys){
    for (unsigned i = 0 ; i < size ; i++){
        Insert(root, Keys[i]);
    }
}

// MINIMUM / MAXIMUM
Node Maximum(Node root){
    Node curr = root;
    while ( curr->right != NULL ){
        curr = curr->right;
    }
    return curr;
}

Node Minimum(Node root){
    Node curr = root;
    while ( curr->left != NULL ){
        curr = curr->left;
    }
    return curr;
}

// TREE TRAVERSAL
void Preorder(Node root) {
    if ( root != NULL ){
        cout << root->key << " ";
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

// SUCCESSOR / PREDECCESSOR
Node Successor(Node root){
    // RIGHT CASE
    if ( root->right != NULL ){
        return Minimum(root->right);
    }
    // LEFT CASE
    Node par = root->p, curr = root;
    while ( par != NULL && curr == par->right ){
        curr = par;
        par = par->p;
    }

    return par;
}

Node Predeccessor(Node root){
    // LEFT CASE
    if ( root->left != NULL ){
        return Maximum(root->left);
    }
    // RIGHT CASE
    Node par = root->p, curr = root;
    while ( par != NULL && curr == par->left ){
        curr = par;
        par = par->p;
    }

    return par;
}

int Height(Node root) {
    if ( root->left == NULL && root->right == NULL ){
        return 1;
    }

    unsigned rightNr = 0;
    unsigned leftNr = 0;

    if ( root->right != NULL ){
        rightNr = 1 + Height(root->right);
    }
    if ( root->left != NULL ){
        leftNr = 1 + Height(root->left);
    }

    return ( rightNr > leftNr ) ? rightNr : leftNr;
}

Node Search(Node root, int key){
    Node curr = root;

    while ( curr != NULL && curr->key != key ){
        if ( key < curr->key ){
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return curr;
}

int PerfectlyBalancedAlgo(Node root){
    if ( root->left == NULL && root->right == NULL ){
        return 1;
    }

    int rightNr = 0;
    int leftNr = 0;

    if ( root->right != NULL ){
        rightNr = PerfectlyBalancedAlgo(root->right);
    }
    if ( root->left != NULL ){
        leftNr = PerfectlyBalancedAlgo(root->left);
    }

    if ( leftNr == -1 || rightNr == -1 ){
        return -1;
    }

    if ( abs(leftNr-rightNr) > 1 ){
        return -1;
    }

    return rightNr + leftNr + 1;
}

bool IsPerfectlyBalanced(Node root){
    return ( PerfectlyBalancedAlgo(root) != -1 );
}

Node SearchClosest(Node root, int key){
    Node curr = root;
    Node closest = root;
    int diffAbs = abs(root->key - key);

    while ( curr != NULL ){
        if ( curr->key == key ){
            return curr;
        }
        else if ( abs(curr->key-key) < diffAbs ){
            closest = curr;
            diffAbs = abs(curr->key - key);
        }

        if ( key < curr->key ){
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return closest;
}

void TreeToVector(Node root, vector<Node> &treeVec){
    if ( root != NULL ){
        TreeToVector(root->left, treeVec);
        treeVec.push_back(root);
        TreeToVector(root->right, treeVec);
    }
}

bool CheckExistTwoNodesWithSum(Node root, unsigned sum){
    vector<Node> treeVec;
    TreeToVector(root, treeVec);

    int left = 0;
    int right = treeVec.size()-1;

    while ( left < right ){
        if ( treeVec[left]->key + treeVec[right]->key == sum ){
            return true;
        }
        else {
            if ( treeVec[left]->key + treeVec[right]->key < sum ){
                left++;
            }
            if ( treeVec[left]->key + treeVec[right]->key > sum ){
                right--;
            }
        }
    }

    return false;
}

void PrintPath(vector<Node> path){
    for (unsigned i = 0 ; i < path.size() ; i++){
        cout << path[i]->key << " ";
    }
    cout << "   ";
}

bool PathTo(Node root, int key, vector<Node>& path) {
    Node curr = root;

    while ( curr != NULL && curr->key != key ){
        path.push_back(curr);

        if ( key < curr->key ){
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    if ( curr == NULL ){
        path.clear();
        return false;
    }

    path.push_back(curr);
    return true;
}

void PrintPathFromTo(Node root, int key1, int key2){
    vector<Node> path1, path2, path;

    bool found1 = PathTo(root, key1, path1);
    bool found2 = PathTo(root, key2, path2);

    if ( !found1 || !found2 ){
        cout << "PATH TO NODE NOT FOUND";
        return;
    }

    unsigned i;
    for (i = 0 ; i < path1.size() && i < path2.size() ; i++){
        if ( path1[i]->key != path2[i]->key ){
            break;
        }
    }

    for (unsigned j = path1.size()-1 ; j >= i ; j--){
        path.push_back(path1[j]);
    }
    for (unsigned j = i-1 ; j < path2.size() ; j++){
        path.push_back(path2[j]);
    }

    PrintPath(path);
}

void PrintPathsWithSum(Node curr, unsigned val, unsigned sum){
    static vector<Node> path;

    path.push_back(curr);
    val += curr->key;

    if ( val == sum ){
        PrintPath(path);
    }
    else if ( val < sum ){
        if ( curr->left != NULL ){
            PrintPathsWithSum(curr->left, val, sum);
        }
        if ( curr->right != NULL ){
            PrintPathsWithSum(curr->right, val, sum);
        }
    }

    path.pop_back();
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

int main()
{
    Node tree = NULL;
    int Arr[] = {8, 2, 15, 1, 5, 10, 20, 4, 7, 18, 22, 3}; // Not Balanced

    InsertArr(&tree, 12, Arr);

    cout << "TREE 1\n";
    cout << "Inorder: "; Inorder(tree); cout << "\n\n";
    cout << "Height: " << Height(tree); cout << '\n';
    cout << "Perfectly Balanced: " << IsPerfectlyBalanced(tree); cout << '\n';
    cout << "Exist 2 Nodes with sum 12: " << CheckExistTwoNodesWithSum(tree, 12); cout << '\n';
    cout << "Successor of 2: " << Successor(Search(tree, 2))->key; cout << '\n';
    cout << "Successor of 7: " << Successor(Search(tree, 7))->key; cout << '\n';
    cout << "Closest to 6: " << SearchClosest(tree, 6)->key; cout << '\n';
    cout << "Path from 3 to 22: "; PrintPathFromTo(tree, 3, 22); cout << '\n';
    cout << "Path with sum 22: "; PrintPathsWithSum(tree, 0, 22); cout << '\n';
    cout << "Print Levels: "; PrintLevels(tree); cout << '\n';
 
    Node tree2 = NULL;
    int Arr2[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9 ,11, 13, 15}; // Perfectly Balanced

    InsertArr(&tree2, 15, Arr2);

    cout << "\nTREE 2\n";
    cout << "Inorder: "; Inorder(tree2); cout << "\n\n";
    cout << "perfectly Balanced: " << IsPerfectlyBalanced(tree2); cout << '\n';

}