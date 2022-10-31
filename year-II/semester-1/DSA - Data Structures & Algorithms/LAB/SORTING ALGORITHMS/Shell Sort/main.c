#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define POPULATE_TYPE 3   // 0 - RANDOM
                          // 1 - WORST CASE
                          // 2 - KEYBOARD INPUT
                          // 3 - FILE INPUT

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
  for (int i = 0 ; i < SIZE ; i++){
    printf("%d ", Arr[i]);
  }
  printf("\n");
}

void insert(int *Arr, unsigned elemIndex, unsigned insertIndex, unsigned step){
  int aux = Arr[elemIndex];

  for (unsigned i = elemIndex ; i > insertIndex ; i -= step){
    Arr[i] = Arr[i-step];
  }
  Arr[insertIndex] = aux;
}

void shell_sort(int *Arr){
  unsigned j;
  static unsigned step[] = {7, 4, 3, 2, 1};

  for (unsigned stepNr = 0 ; stepNr < 5 ; stepNr++){
      for (unsigned i = step[stepNr] ; i < SIZE ; i++){
        for (j = i ; j > 0 ; j -= step[stepNr]){
            if ( Arr[i] > Arr[j-1] ){
                insert(Arr, i, j, step[stepNr]);
                break;
            }
        }
        if ( j == 0 ){
            insert(Arr, i, 0, step[stepNr]);
        }
        print_array(Arr);
    }
  }
}

int main(){
  FILE *stream_in = fopen("../arr.txt", "r");
  int Arr[SIZE];

  populate_array(Arr, stream_in);
  print_array(Arr);

  shell_sort(Arr);

  return 0;
}
