#include <stdio.h>
#include <stdlib.h>

typedef struct _llist{
  int val;
  struct _llist *next;
}llist;

/// -------------- PRINTING FUNCTIONS (CIRCULAR LINKED LIST) --------------

void print_llist_node(llist *cntNode){
  printf("%p %d -next-> %p\n", cntNode, cntNode->val, cntNode->next);
}

void print_cllist(llist *root, int n){
  llist *cntCLNode = root;

  if ( root == NULL){
    printf("%p - NULL\n", root);
  }
  for ( int i = 0 ; i < n ; i++){
    print_llist_node( cntCLNode );
    cntCLNode = cntCLNode->next;
  }
}

/// -------------- CREATING FUNCTION (CIRCULAR LINKED LIST) --------------

llist *new_cllist(int n){
  llist *root = NULL;
  if (n > 0){
    root = (llist*)malloc(sizeof(llist));
    llist *crtLNode = root;

    for (int i = 0 ; i < n ; i++){
      crtLNode->val = i;

      if ( i < n - 1){
        crtLNode->next = (llist*)malloc(sizeof(llist));
        crtLNode = crtLNode->next;
      }
      else {
        crtLNode->next = root;
      }
    }
  }

  return root;
}

/// -------------- REMOVING FUNCTION (CIRCULAR LINKED LIST) --------------

llist *remove_middle(llist *root, int *n){
  llist *crtLNode = root;

  for (int i = 0 ; i < (*n)/2 - 1 ; i++){
    crtLNode = crtLNode->next;
  }

  llist *auxLNode = crtLNode->next;
  crtLNode->next = crtLNode->next->next;
  auxLNode = NULL;

  (*n)--;
  return root;
}

int main(){
  llist *root;
  unsigned rootSize;

  printf("List Size: ");
  scanf("%u",&rootSize);

  root = new_cllist( rootSize );
  print_cllist(root, 2*rootSize);
  printf("\n");

  if ( rootSize == 1){
    root = NULL;
  }
  else {
    remove_middle(root, &rootSize );
  }
  print_cllist(root, 2*rootSize);

  return 0;
}
