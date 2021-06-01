#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define POPULATE_TYPE 3   // 0 - WORST CASE
                          // 1 - RANDOM
                          // 2 - KEYBOARD INPUT
                          // 3 - FILE INPUT

unsigned swaps = 0,
         comparisons = 0,
         steps = 0;

void populate_array(int *Arr, FILE *stream){
  switch ( POPULATE_TYPE ){
    case 0:
      srand(time(NULL));

      for (unsigned i = 0 ; i < SIZE ; i++){
        Arr[i] = rand() % SIZE + 1;
      }
      break;
    case 1:
      for (unsigned i = 0 ; i < SIZE ; i++){
        Arr[i] = SIZE - i;
      }
      break;
    case 2:
      for (unsigned i = 0 ; i < SIZE ; i++){
        scanf("%d", &Arr[i]);
      }
      break;
    case 3:
      for (unsigned i = 0 ; i < SIZE ; i++){
        fscanf(stream, "%d", &Arr[i]);
      }
      break;
  }
}

void print_array(int *Arr){
  printf("Step %u: ", steps++);
  for (int i = 0 ; i < SIZE ; i++){
    printf("%d ", Arr[i]);
  }
  printf("\n");
}

void swap(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
  swaps++;
}

void selection_sort(int *Arr){
  int min;
  unsigned mindex;
  for (unsigned i = 0 ; i < SIZE - 1 ; i++){
    min = Arr[i];
    mindex = i;
    for (unsigned j = i + 1 ; j < SIZE ; j++){
      if ( Arr[j] < min ){
        min = Arr[j];
        mindex = j;
      }
      comparisons++;
    }
    swap(&Arr[i], &Arr[mindex]);
    print_array(Arr);
  }
}

int main(){
  FILE *stream_in = fopen("../arr.txt", "r");
  int Arr[SIZE];

  populate_array(Arr, stream_in);
  print_array(Arr);

  selection_sort(Arr);

  printf("\nSwaps: %u\n", swaps);
  printf("Comparisons: %u\n", comparisons);

  return 0;
}
