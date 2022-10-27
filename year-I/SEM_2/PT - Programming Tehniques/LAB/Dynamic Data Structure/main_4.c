#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ESP 0.001

typedef struct _btree{
  float val;
  struct _btree *left, *right;
}btree;

/// -------------- PRINTING FUNCTIONS (BINARY TREE) --------------

void print_btree_node(btree *cntNode){
  printf("%p <-left- %p %f -right-> %p\n", cntNode->left, cntNode, cntNode->val, cntNode->right);
}

void print_tree_preorder(btree *cntNode){
  if ( cntNode != NULL ){
    print_btree_node( cntNode );
    print_tree_preorder(cntNode->left);
    print_tree_preorder(cntNode->right);
  }
}

void print_tree_inorder(btree *cntNode){
    if (cntNode != NULL){
      print_tree_inorder(cntNode->left);
      print_btree_node( cntNode );
      print_tree_inorder(cntNode->right);
    }
}

void print_tree_postorder(btree *cntNode){
    if (cntNode != NULL){
      print_tree_postorder(cntNode->left);
      print_tree_postorder(cntNode->right);
      print_btree_node( cntNode );
    }
}

/// -------------- CREATING FUNCTIONS (BINARY TREE) --------------

btree *add_btree_node(btree *BTNode, float val){
  if ( BTNode == NULL ){
    BTNode = (btree*)malloc(sizeof(btree));

    BTNode->val = val;
    BTNode->left = NULL;
    BTNode->right = NULL;
  }
  else {
    if ( fabs(val - BTNode->val) >= ESP ){
      if ( val < BTNode->val ){
        BTNode->left = add_btree_node(BTNode->left, val);
      }
      else {
        BTNode->right = add_btree_node(BTNode->right, val);
      }
    }
  }

  return BTNode;
}

void get_btree(btree **root, unsigned size){
  float val;

  for ( int i = 0 ; i < size ; i++ ){
    printf("Nr %d: ", i);
    scanf("%f", &val);

    *root = add_btree_node(*root, val);
  }
}

int main(){
  btree *root = NULL;
  unsigned rootSize;

  printf("List Size: ");
  scanf("%u",&rootSize);

  get_btree(&root, rootSize);

  char *order = malloc(20*sizeof(char));
  printf("Print Order(preorder; inorder; postorder): ");
  char extraENDL = getchar();
  scanf("%s", order);

  if ( !strcmp(order,"preorder") ){
    print_tree_preorder(root);
  }
  else if ( !strcmp(order,"inorder") ){
    print_tree_inorder(root);
  }
  else if ( !strcmp(order,"postorder") ){
    print_tree_postorder(root);
  }

  return 0;
}
