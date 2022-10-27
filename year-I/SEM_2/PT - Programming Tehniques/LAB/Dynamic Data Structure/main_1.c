#include <stdio.h>
#include <stdlib.h>

typedef struct _dllist{
  int key;
  struct _dllist *prev, *next;
}dllist;

/// -------------- PRINTING FUNCTIONS (DOUBLE-LINKED LIST) --------------

void print_dllist_node(dllist *cntNode){
  printf("%p <-prev- %p %d -next-> %p\n", cntNode->prev, cntNode, cntNode->key, cntNode->next);
}

void print_dllist(dllist *root){
  if ( root == NULL){
    printf("%p - NULL\n", root);
  }
  for ( dllist *cntDLNode = root; cntDLNode != NULL ; cntDLNode = cntDLNode->next ){
    print_dllist_node( cntDLNode );
  }
}

/// -------------- CREATING FUNCTIONS ( (INVERTED) DOUBLE-LINKED LIST) --------------

dllist *new_dllist(dllist *prevDLNode, unsigned index, unsigned size){
  dllist *crtDLNode = (dllist*)malloc(sizeof(dllist));

  // Value
  crtDLNode->key = index;
  // Previous Double-Linked List
  crtDLNode->prev = prevDLNode;
  // Next Double-Linked List
  if ( index < size ){
    crtDLNode->next = new_dllist( crtDLNode, index + 1, size);
    return crtDLNode;
  }
  else {
    return NULL;
  }
}

dllist *invert_dllist(dllist *DLList){
  dllist *newDLNode = (dllist*)malloc(sizeof(dllist));
  newDLNode->next = NULL;

  for ( dllist *crtDLNode = DLList ; crtDLNode != NULL; crtDLNode = crtDLNode->next ){
    newDLNode->key = crtDLNode->key;

    if ( crtDLNode->next != NULL ){
      newDLNode->prev = (dllist*)malloc(sizeof(dllist));
      (newDLNode->prev)->next = newDLNode;

      newDLNode = newDLNode->prev;
    }
  }
  newDLNode->prev = NULL;

  return newDLNode;
}

int main(){
  dllist *root, *invRoot;
  unsigned rootSize;

  printf("Nr of Elems: ");
  scanf("%u",&rootSize);

  root = new_dllist( NULL, 0 , rootSize );
  invRoot = invert_dllist( root );

  print_dllist(root);
  printf("\n\n");
  print_dllist(invRoot);

  return 0;
}
