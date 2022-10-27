#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define POPULATE_TYPE 0   // 0 - RANDOM
                          // 1 - WORST CASE

unsigned swaps = 0,
         comparisons = 0,
         steps = 0;

void populate_array(int *Arr, FILE *stream){
  switch ( POPULATE_TYPE ){
    case 0:
      srand(time(NULL));

      for (unsigned i = 0 ; i < SIZE ; i++){
        Arr[i] = 0;
      }
      for (unsigned i = 0 ; i < SIZE ; i++){
        unsigned randNr = rand() % SIZE;
        if ( !Arr[randNr] ){
          Arr[randNr] = i+1;
        }
        else {
          i--;
        }
      }
      break;
    case 1:
      for (unsigned i = 0 ; i < SIZE ; i++){
        Arr[i] = SIZE - i;
      }
      break;
    default:
      exit(1);
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

void bin_sort(int *Arr){
  int i = 0;

  while ( i < SIZE ){
    if ( Arr[i] == i+1 ){
      i++;
    }
    else{
      swap(&Arr[i], &Arr[Arr[i]-1]);
      print_array(Arr);
    }
  }
}

int main(){
  FILE *stream_in = fopen("../arr.txt", "r");
  int Arr[SIZE];

  populate_array(Arr, stream_in);
  print_array(Arr);

  bin_sort(Arr);

  printf("\nSwaps: %u\n", swaps);
  printf("Comparisons: %u\n", comparisons);

  return 0;
}
