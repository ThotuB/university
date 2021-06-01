#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void populate_array(unsigned arr[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    arr[i] = size - i ;
  }
}

void print_array(unsigned arr[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    printf("%u\n", arr[i]);
  }
}

void bubble_sort(unsigned arr[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    for (unsigned j = i+1 ; j < size ; j++){
      if ( arr[i] > arr[j] ){
        unsigned temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int main(){
  unsigned sizeArr = 10000;
  unsigned *Arr = NULL;
  clock_t ticks;

  for ( ; sizeArr <= 100000 ; sizeArr += 10000){
    Arr = (unsigned*)malloc(sizeArr * sizeof(unsigned));

    populate_array(Arr, sizeArr);
    //print_array(Arr, sizeArr);
    ticks = clock();
    bubble_sort(Arr, sizeArr);
    ticks = clock() - ticks;
    //print_array(Arr, sizeArr);

    printf("Size: %u\n", sizeArr);
    printf("\t- Ticks: %li\n", ticks);
    printf("\t- Time: %lfs\n\n", ((double)(ticks))/CLOCKS_PER_SEC);

    free(Arr);
  }

  return 0;
}
