#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define LIM_RAND 200

int *get_array(unsigned size){
  int *arr = malloc(size * sizeof(int));

  for (unsigned i = 0 ; i < size ; i++){
    arr[i] = rand() % LIM_RAND - LIM_RAND/2;
  }

  return arr;
}

void print_array(int *arr, unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void find_peaks(int *arr, unsigned left, unsigned right){
  unsigned mid = (left + right)/2;

  if ( arr[mid-1] <= arr[mid] && arr[mid+1] <= arr[mid] ){
    printf(" - Local maximum: %d\n", arr[mid]);
  }
  else if ( arr[mid-1] >= arr[mid] && arr[mid+1] >= arr[mid] ){
    printf(" - Local minimum: %d\n", arr[mid]);
  }

  if ( left != right ){
    if ( left != mid ){
      find_peaks(arr, left, mid - 1);
    }
    find_peaks(arr, mid + 1, right);
  }
}

int main(){
  int *nums = get_array(SIZE);

  print_array(nums, SIZE);

  printf("\nPeaks:\n");
  find_peaks(nums, 1, SIZE - 2);
  return 0;
}
