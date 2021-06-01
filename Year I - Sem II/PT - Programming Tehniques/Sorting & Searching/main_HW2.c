#include <stdio.h>
#include <stdlib.h>

#define RAND_LIM 100

long long unsigned cntNorm = 0, cntBin = 0;

/// ----------- ARRAY FUNCTIONS -----------

void fillArr(unsigned Arr[], unsigned size){
  for (unsigned i = 0; i < size; i++){
    Arr[i] = rand() % RAND_LIM;
  }
}

void printArr(unsigned Arr[], unsigned size){
  printf("\n");
  for (unsigned i = 0; i < size; i++){
    printf("%u ",Arr[i]);
  }
  printf("\n\n");
}

int compare(const void * a, const void * b)
{
  return ( *(unsigned*)a - *(unsigned*)b );
}

/// ----------- SEARCH FUNCTIONS -----------

int binarySearch(unsigned Arr[],unsigned begin, unsigned end, unsigned nr){
  unsigned mid = (begin + end)/2;

  cntBin++;

  if ( begin == end && nr != Arr[mid]){
    return -1;
  }

  if ( nr < Arr[mid] ){
    return binarySearch(Arr, begin, mid - 1, nr);
  }
  else if ( nr > Arr[mid] ){
    return binarySearch(Arr, mid + 1, end, nr);
  }
  else if ( nr == Arr[mid] ){
    return mid;
  }
}

int normalSearch(unsigned Arr[], unsigned size, unsigned nr){
  for (unsigned i = 0; i < size ; i++){
    cntNorm++;

    if ( nr == Arr[i] ){
      return i;
    }
  }

  return -1;
}

int main(){
  unsigned N, X;
  unsigned size;
  unsigned *Vec = malloc(sizeof(unsigned));
  int posNorm, posBin;

  printf("N: ");
  scanf("%u", &N);
  printf("X: ");
  scanf("%u", &X);

  size = 1 << N;
  printf("\nsize - %u\n\n", size);

  Vec = realloc(Vec, size*sizeof(unsigned));
  fillArr(Vec, size);

  /// NORMAL SEARCH
  //printArr(Vec, size);

  posNorm = normalSearch(Vec, size, X);
  printf("Normal Search Counter: %llu\n", cntNorm);
  if ( posNorm != -1){
    printf("X - found on position: %u\n\n", posNorm);
  }
  else {
    printf("X - not found\n\n");
  }

  /// BINARY SEARCH
  //printArr(Vec, size);

  qsort(Vec, size, sizeof(unsigned), compare);
  posBin = binarySearch(Vec, 0, size - 1, X);
  printf("Binary Search Counter: %llu\n", cntBin);
  if ( posBin != -1){
    printf("X - found on position: %d\n", posBin);
  }
  else {
    printf("X - not found\n");
  }

  return 0;
}
