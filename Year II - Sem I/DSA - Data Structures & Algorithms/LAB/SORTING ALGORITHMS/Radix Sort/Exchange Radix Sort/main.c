#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define POPULATE_TYPE 3   // 0 - RANDOM
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

// void print_binary(int nr, unsigned bits){
//   printf("\n\t");
//   for (unsigned i = 0 ; i < bits ; i++){
//     printf("%d", ( nr & ( 1 << (bits-i-1) ) ) ? 1 : 0 );
//   }
// }

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

unsigned get_bit(unsigned nr, int bitNr){
    return (nr & (1<<bitNr)) ? 1 : 0;
}

void radix_exchange_sort(int *Arr, unsigned left, unsigned right, int bit){
    int i = left;
    int j = right;

    if ( left != right && bit >= 0 ){
        do {
            while ( get_bit(Arr[i], bit) == 0 && i < j ) i++;
            while ( get_bit(Arr[j], bit) == 1 && i < j ) j--;
            swap(&Arr[i], &Arr[j]);
        }while (i != j);
        print_array(Arr);
        radix_exchange_sort(Arr, left, j-1, bit-1);
        radix_exchange_sort(Arr, j, right, bit-1);
    }
}

int main(){
    FILE *stream_in = fopen("../../arr.txt", "r");
    int Arr[SIZE];

    populate_array(Arr, stream_in);
    print_array(Arr);

    radix_exchange_sort(Arr, 0, SIZE-1, 3);

    printf("\nSwaps: %u\n", swaps);
    printf("Comparisons: %u\n", comparisons);

    return 0;
}
