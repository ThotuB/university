#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DETAILS 1 // true / false - prints pointer details

unsigned size = 0;

typedef struct _dllist {
  char *name;
  struct _dllist *prev, *next;
} dllist;

/// --------------- PRINTING FUNCTIONS ---------------

void print_dllist_node(dllist *node){
  if ( DETAILS ){
    printf("%p <-prev- %p ", node->prev ,node);
  }
  printf("%s", node->name);
  if ( DETAILS ){
    printf(" -next-> %p", node->next);
  }
  printf("\n");
}

void print_cdllist(dllist *root, int size){
  if ( root == NULL){
    printf("%p - NULL\n", root);
  }
  for ( dllist *node = root; node != NULL && size ; node = node->next, size-- ){
    print_dllist_node( node );
  }
  printf("\n");
}

/// --------------- NODE ELIMINATING FUNCTION ---------------

dllist *delete_cdlnode(dllist *root, dllist *node){
  if (node == root){ // moving root ( if initial root is to be eliminated )
    root = root->next;
  }
  if (root == root->next){ // eliminating last node
    return NULL;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;

  return root;
}

/// --------------- GETTING/ADDING FUNCTIONS (CIRCULAR DOUBLE-LINKED LIST) ---------------

dllist *get_dlnode(dllist *prev, dllist *next, char *name){
  dllist *node = malloc(sizeof(dllist));

  node->name = name;
  node->prev = prev;
  node->next = next;

  return node;
}

dllist *add_dlnode(dllist *root, char *name, dllist **tail){
  if ( root == NULL ){
    root = get_dlnode(NULL, NULL, name); // setting initial root
    *tail = root; // setting initial tail
  }
  else {
    dllist *node = root, *prev = root, *next = root;

    if ( strcmp( root->name, name ) < 0 ){ // adding to the right
      next = next->next;
      for ( ; node->next != NULL && strcmp( node->next->name, name ) < 0 ; node = node->next ){
        prev = prev->next;
        next = next->next;
      }
      node = get_dlnode(prev, next, name);
      prev->next = node;
      if ( next != NULL ){ // adding in the middle
        next->prev = node;
      }
      else {
        *tail = node; // setting new tail ( if node was added at the end )
      }
    }
    else if ( strcmp( root->name, name ) > 0 ){ // adding to the left
      node = get_dlnode(prev, next, name);
      next->prev = node;

      root = node; // setting added node as root
    }
  }

  return root;
}

dllist *get_cdllist_names(dllist **root, FILE *stream){
  char *name = malloc(20*sizeof(char));
  dllist *tail = malloc(sizeof(dllist));

  while ( fscanf( stream, "%19s", name) == 1){
    *root = add_dlnode(*root, name, &tail);
    size++;
    //printf("%s\n", name);
    name = malloc(20*sizeof(char));
  }

  (*root)->prev = tail;
  tail->next = *root;

  return *root;
}

/// --------------- GAME FUNCTION ---------------

void play_game(dllist **root){
  dllist *node = *root;
  unsigned n, dir;

  do {
    printf("Direction (0 - clockwise; 1 - counter-clockwise): ");
    scanf("%u", &dir);
  }while ( dir != 0 && dir != 1);
  if ( dir ){ // setting root as prev node ( counter-clockwise )
    node = node->prev;
  }

  printf("N: ");
  scanf("%u", &n);

  for (unsigned i = 1 ; *root != NULL ; i = (i + 1) % n){
    if ( i % n != 0 ){
      printf("Skipping %s\n", node->name);
    }
    else {
      printf("Eliminating %s\n", node->name);
      *root = delete_cdlnode(*root, node);
    }

    if ( dir ){
      node = node->prev;
    }
    else {
      node = node->next;
    }
  }

  printf("Game Over");
}

int main(){
  FILE *f_names = fopen("names.txt", "r");
  dllist *root = NULL;

  root = get_cdllist_names(&root, f_names);
  print_cdllist(root, size);

  play_game(&root);

  return 0;
}
