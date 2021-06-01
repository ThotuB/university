#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _dllist{
  int key;
  struct _dllist *prev, *next;
}dllist;

typedef struct _llist{
  int key;
  struct _llist *next;
}llist;

/// -------------- PRINTING FUNCTIONS (DOUBLE-LINKED LIST) --------------

void print_dllist_node(dllist *cntNode){
  printf("%p <-prev- %p %d -next-> %p\n", cntNode->prev ,cntNode, cntNode->key, cntNode->next);
}

void print_dllist(dllist *root){
  if ( root == NULL){
    printf("%p - NULL\n", root);
  }
  for ( dllist *cntDLNode = root; cntDLNode != NULL ; cntDLNode = cntDLNode->next ){
    print_dllist_node( cntDLNode );
  }
  printf("\n");
}

/// -------------- PRINTING FUNCTIONS (LINKED LIST) --------------

void print_llist_node(llist *cntNode){
  printf("%p %d -next-> %p\n", cntNode, cntNode->key, cntNode->next);
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

llist *new_llist(unsigned index, unsigned size){
  llist *crtLNode = (llist*)malloc(sizeof(llist));

  // Value
  crtLNode->key = index;
  // Next Linked List
  if ( index < size ){
    crtLNode->next = new_llist(index + 1, size);
    return crtLNode;
  }
  else {
    return NULL;
  }
}

/// -------------- SPLITTING FUNCTIONS --------------

dllist *llist2dllist(llist **cntLL, dllist **rootDLL, unsigned maxSize){
  if ( (*cntLL) != NULL && maxSize > 0){
    *rootDLL = (dllist*)malloc(sizeof(dllist));

    dllist *nodeDL = *rootDLL;

    nodeDL->prev = NULL;
    for ( ; (*cntLL) != NULL && (*cntLL)->key < maxSize; (*cntLL) = (*cntLL)->next){
      nodeDL->key = (*cntLL)->key;

      if ( (*cntLL)->next != NULL && (*cntLL)->next->key < maxSize){
        nodeDL->next = (dllist*)malloc(sizeof(dllist));
        (nodeDL->next)->prev = nodeDL;

        nodeDL = nodeDL->next;
      }
    }
    nodeDL->next = NULL;
  }

  return *rootDLL;
}

void split_llist(llist *rootLL, dllist **rootDLL1, dllist **rootDLL2, unsigned splitKey){
  llist *cntLL = rootLL;

  *rootDLL1 = llist2dllist(&cntLL, rootDLL1, splitKey);
  *rootDLL2 = llist2dllist(&cntLL, rootDLL2, UINT_MAX);
}

int main(){
  llist *root = NULL;
  unsigned rootSize, splitKey;

  dllist *rootFirst = NULL;
  dllist *rootSecond = NULL;

  printf("Nr of Elems: ");
  scanf("%u",&rootSize);

  root = new_llist( 0 , rootSize );

  print_llist(root);

  printf("Split Key: ");
  scanf("%u",&splitKey);

  split_llist(root, &rootFirst, &rootSecond, splitKey);

  print_dllist( rootFirst );
  print_dllist( rootSecond );
  return 0;
}
