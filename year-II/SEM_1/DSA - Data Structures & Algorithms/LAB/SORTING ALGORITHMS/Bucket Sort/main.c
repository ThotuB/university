#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void print_bucket(int **bucket, unsigned * count, unsigned size){
    for (unsigned i = 0 ; i < size ; i++){
        printf("%d: ", i);
        for (unsigned j = 0 ; j < count[i] ; j++){
            printf("%d ", bucket[i][j]);
        }
        printf("\n");
    }
}

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
    swaps++;
}

unsigned get_bits(unsigned nr, int bitNr, unsigned nrOfBits){
    return (nr >> bitNr) & (~(~0 << nrOfBits));
}

void radix_exchange_sort(int *Arr, unsigned mask){
    int bits = (int)ceil(log2(SIZE));
    unsigned bucketArrSize = pow(2, mask);
    int **bucketArr = (int**)calloc(bucketArrSize, sizeof(int*));
    unsigned *count = (unsigned*)calloc(bucketArrSize, sizeof(unsigned));

    for (unsigned i = 0 ; i < SIZE ; i++){
        unsigned index = get_bits(Arr[i], bits-mask, mask);
        count[index]++;
        bucketArr[index] = (int*)realloc(bucketArr[index], count[index] * sizeof(int));
        unsigned j;
        for ( j = count[index] - 1 ; j > 0 ; j--){
            if ( Arr[i] < bucketArr[index][j-1] ){
                swap(&bucketArr[index][j], &bucketArr[index][j-1]);
            }
            else {
                break;
            }
            comparisons++;
        }
        bucketArr[index][j] = Arr[i];
    }
    print_bucket(bucketArr, count, bucketArrSize);
    unsigned k = 0;
    for (unsigned index = 0 ; index < bucketArrSize ; index++){
        for (unsigned i = 0 ; i < count[index] ; i++){
            Arr[k] = bucketArr[index][i];
            k++;
        }
        count[index] = 0;
    }
    print_array(Arr);
}

int main(){
    FILE *stream_in = fopen("../../arr.txt", "r");
    int Arr[SIZE];

    populate_array(Arr, stream_in);
    print_array(Arr);

    radix_exchange_sort(Arr, 2);

    printf("\nSwaps: %u\n", swaps);
    printf("Comparisons: %u\n", comparisons);

    return 0;
}
