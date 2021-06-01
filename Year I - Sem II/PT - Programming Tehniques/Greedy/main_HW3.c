#include <stdio.h>
#include <stdlib.h>

typedef struct hufftable {
  char c;
  unsigned val;
}hufftable_t;

void print_hufftable_node(hufftable_t node){
  switch ( node.c ){
    case '\n': printf("newline"); break;
    case ' ': printf("space"); break;
    default: printf("%c", node.c); break;
  }
  printf(" - %u\n", node.val);
}

void print_hufftable(hufftable_t *table, unsigned size){
  for ( unsigned i = 0 ; i < size ; i++){
    print_hufftable_node(table[i]);
  }
  printf("\n");
}

hufftable_t push_hufftable(char c, unsigned val){
  hufftable_t table;

  table.c = c;
  table.val = val;

  return table;
}

hufftable_t *get_hufftable(FILE *stream, unsigned *size){
  hufftable_t *table = malloc(0);

  for (char c = fgetc(stream); c != EOF; c= fgetc(stream)){
    unsigned newChar = 1;

    for ( unsigned i = 0 ; i < (*size) ; i++){
      if ( c == table[i].c ){
        table[i].val++;
        newChar = 0;
        break;
      }
    }

    if ( newChar ){
      table = realloc(table, ((*size) + 1) * sizeof(hufftable_t));
      table[(*size)] = push_hufftable(c, 1);

      (*size)++;
    }
  }

  return table;
}

void order_hufftable(hufftable_t *table, unsigned size){
  for ( unsigned i = 0 ; i < size - 1; i++){
    for ( unsigned j = i + 1 ; j < size ; j++){
      if ( table[i].val > table[j].val ){
        hufftable_t aux = table[i];
        table[i] = table[j];
        table[j] = aux;
      }
    }
  }
}

int main(){
  FILE *file_in = fopen("file.txt", "r");

  unsigned size = 0;
  hufftable_t *charAppear = get_hufftable(file_in, &size);

  print_hufftable(charAppear, size);

  order_hufftable(charAppear, size);

  print_hufftable(charAppear, size);

  return 0;
}
