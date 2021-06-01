#include <stdio.h>
#include <stdlib.h>

#define N 20
#define RAND_LIM 100

void printArr(int Arr[], int n){
  for (int i=0 ; i < n ; i++){
    printf("%d ", Arr[i]);
  }
  printf("\n");
}

/// ---------- INSERTION SORT FUNCTIONS --------------

void insertionSort(int Arr[], int size){
  int j;

  for (int i = 0 ; i < size ; i++){
    int aux = Arr[i];

    for (j = i - 1 ; j >= 0 && Arr[j] > aux; j--){
      Arr[j + 1] = Arr[j];
    }
    Arr[j + 1] = aux;
  }
}

/// -*-*-*-*-*-*-*- MAIN FUNCTION -*-*-*-*-*-*-*-

int main(){
  int Vec[N];
  for (int i=0 ; i < N ; i++){
    Vec[i] = rand() % RAND_LIM;
  }
  printArr(Vec, N);
  insertionSort(Vec, N);
  printArr(Vec, N);
  return 0;
}
