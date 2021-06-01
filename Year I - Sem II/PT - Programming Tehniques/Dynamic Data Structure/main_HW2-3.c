/* Problem 2:
 * - add integer numbers from a file ("numbers.txt") to a binary search tree
 * - print binary tree in preorder
 * - create a linked list from the nubers of the binary tree in ascending order
 * - print the linked list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _btree{
  int val;
  struct _btree *left, *right;
}btree;

typedef struct _llist{
  int val;
  struct _llist *next;
}llist;

/// -------------- PRINTING FUNCTIONS (LINKED LIST) --------------

void print_llist_node(llist *cntNode){
  printf("%p %d -next-> %p\n", cntNode, cntNode->val, cntNode->next);
}

void print_llist(llist *root){
  if ( root == NULL){
    printf("%p - NULL\n", root);
  }
  for ( llist *cntDLNode = root; cntDLNode != NULL ; cntDLNode = cntDLNode->next ){
    print_llist_node( cntDLNode );
  }
  printf("\n");
}

/// -------------- CREATING FUNCTIONS (LINKED LIST) --------------

llist *get_lnode(llist *node, llist *next, int val){
  node = malloc(sizeof(llist));

  node->val = val;
  node->next = next;

  return node;
}

llist *add_lnode(llist *root, int val){
  if ( root == NULL ){
    root = get_lnode(root, NULL, val);
  }
  else {
    llist *node = root;

    while ( node->next != NULL ){
      node = node->next;
    }
    node->next = get_lnode(node, NULL, val);
  }

  return root;
}

void get_llist_from_btree(llist **rootLL, btree *cntNodeBT){
  if (cntNodeBT != NULL){
    get_llist_from_btree(rootLL, cntNodeBT->left);
    *rootLL = add_lnode(*rootLL, cntNodeBT->val);
    get_llist_from_btree(rootLL, cntNodeBT->right);
  }
}

/// -------------- PRINTING FUNCTIONS (BINARY TREE) --------------

void print_btree_node(btree *cntNode){
  printf("%p <-left- %p %d -right-> %p\n", cntNode->left, cntNode, cntNode->val, cntNode->right);
}

void print_tree_preorder(btree *cntNode){
    if (cntNode != NULL){
      print_btree_node( cntNode );
      print_tree_preorder(cntNode->left);
      print_tree_preorder(cntNode->right);
    }
}

/// -------------- CREATING FUNCTIONS (BINARY TREE) --------------

btree *add_btree_node(btree *BTNode, int val){
  if ( BTNode == NULL ){
    BTNode = (btree*)malloc(sizeof(btree));

    BTNode->val = val;
    BTNode->left = NULL;
    BTNode->right = NULL;
  }
  else {
    if ( val < BTNode->val ){
      BTNode->left = add_btree_node(BTNode->left, val);
    }
    else if ( val > BTNode->val ){
      BTNode->right = add_btree_node(BTNode->right, val);
    }
  }

  return BTNode;
}

void get_btree(btree **root, FILE *stream){
  int val;

  while ( fscanf(stream, "%d", &val) == 1){
    *root = add_btree_node(*root, val);
  }
}

int main(){
  FILE *numbers_in = fopen("numbers.txt", "r");
  btree *rootBT = NULL;
  llist *rootLL = NULL;

  get_btree(&rootBT, numbers_in);

  printf("Binary Tree:\n");
  print_tree_preorder(rootBT);

  get_llist_from_btree(&rootLL, rootBT);

  printf("\nLinked List:\n");
  print_llist(rootLL);
  return 0;
}
