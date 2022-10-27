#include <stdio.h>
#include <stdlib.h>

#define RAND_LIM 100

long long unsigned swapMerge = 0, swapInsert = 0;

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

void copyArr(unsigned Dest[], unsigned Src[], unsigned size){
  for (unsigned i = 0; i < size; i++){
    Dest[i] = Src[i];
  }
}

/// ----------- SORT FUNCTIONS -----------

void insertionSort(unsigned Arr[], unsigned size){
  int j;
  for (int i = 0 ; i < size ; i++){
    int aux = Arr[i];

    for (j = i - 1 ; j >= 0 && Arr[j] > aux; j--){
      swapInsert++;
      Arr[j + 1] = Arr[j];
    }
    Arr[j + 1] = aux;
  }
}

void merge(unsigned Arr1[], unsigned size1, unsigned Arr2[], unsigned size2){
  unsigned Temp[size1 + size2];
  unsigned i = 0, j = 0, cntTemp = 0;

  while ( i < size1 && j < size2 ){
    if ( Arr1[i] < Arr2[j]){
      Temp[cntTemp] = Arr1[i];
      i++;
    }
    else {
      Temp[cntTemp] = Arr2[j];
      j++;
    }
    swapMerge++;
    cntTemp++;
  }

  while ( i < size1 ){
    Temp[cntTemp] = Arr1[i];
    i++;
    swapMerge++;
    cntTemp++;
  }

  while( j < size2 ){
    Temp[cntTemp] = Arr2[j];
    j++;
    swapMerge++;
    cntTemp++;
  }

  copyArr(Arr1, Temp, size1 + size2);
  swapMerge += (size1 + size2);
}

void mergeSort(unsigned Arr[], unsigned begin, unsigned end){
  if (begin < end){
    unsigned mid = (begin + end)/2;

    mergeSort(Arr, begin, mid);
    mergeSort(Arr, mid + 1, end);

    merge(Arr + begin, mid - begin + 1, Arr + mid + 1, end - mid);
  }

}

int main(){
  unsigned size;
  unsigned *Vec1 = malloc(sizeof(unsigned));
  unsigned *Vec2 = malloc(sizeof(unsigned));

  printf("N: ");
  scanf("%u", &size);

  Vec1 = realloc(Vec1, size*sizeof(unsigned));
  Vec2 = realloc(Vec2, size*sizeof(unsigned));
  fillArr(Vec1, size);
  copyArr(Vec2, Vec1, size);

  /// INSERTION SORT

  //printArr(Vec1, size);
  insertionSort(Vec1, size);
  printf("Insertion Sort Swap Counter: %llu", swapInsert);
  //printArr(Vec1, size);

  /// MERGE SORT

  //printArr(Vec2, size);
  mergeSort(Vec2, 0, size - 1);
  printf("\nMerge Sort Swap Counter: %llu", swapMerge);
  //printArr(Vec1, size);

  return 0;
}
