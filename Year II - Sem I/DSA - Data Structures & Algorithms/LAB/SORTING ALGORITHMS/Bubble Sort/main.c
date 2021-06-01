#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define POPULATE_TYPE 1   // 0 - RANDOM
                          // 1 - WORST CASE
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
  printf("Step %u: \t", steps++);
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

void bubble_sort(int *Arr){
  int flag;

  do{
    flag = 0;
    for (unsigned i = 0 ; i < SIZE - 1 ; i++){
      if ( Arr[i] > Arr[i+1] ){
        swap(&Arr[i], &Arr[i+1]);
        flag = 1;
      }
      comparisons++;
    }
    print_array(Arr);
  }while(flag);
}

int main(){
  FILE *stream_in = fopen("../arr.txt", "r");
  int Arr[SIZE];

  populate_array(Arr, stream_in);
  print_array(Arr);

  bubble_sort(Arr);

  printf("\nSwaps: %u\n", swaps);
  printf("Comparisons: %u\n", comparisons);

  return 0;
}
