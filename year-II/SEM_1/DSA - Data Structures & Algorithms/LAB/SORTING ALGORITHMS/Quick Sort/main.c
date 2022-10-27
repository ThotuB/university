#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7

#define POPULATE_TYPE 0   // 0 - RANDOM
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

void quick_sort(int *Arr, unsigned left, unsigned right){
    unsigned i = left;
    unsigned j = right;
    unsigned pivotPos = (left+right)/2;
    int pivot = Arr[pivotPos];

    if ( left != right ){
      do {
          while (Arr[i] < pivot) i++;
          while (Arr[j] > pivot) j--;
          comparisons += i - left + right - j;
          printf("%d - %d :%d(%d) <-> %d(%d)\n",left, right, Arr[i],i, Arr[j],j);
          if ( i <= j ){
              swap(&Arr[i], &Arr[j]);
              i++; j--;
          }
          print_array(Arr);
      }while (i <= j);

      quick_sort(Arr, left, j);
      quick_sort(Arr, i, right);
    }
}

int main(){
    FILE *stream_in = fopen("../arr.txt", "r");
    int Arr[SIZE];

    populate_array(Arr, stream_in);
    print_array(Arr);

    quick_sort(Arr, 0, SIZE-1);

    printf("\nSwaps: %u\n", swaps);
    printf("Comparisons: %u\n", comparisons);

    return 0;
}
