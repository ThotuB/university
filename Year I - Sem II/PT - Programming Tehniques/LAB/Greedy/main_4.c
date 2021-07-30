#include <stdio.h>
// didn't really undersand the task

#define SIZE 13

/// ------------------ METHOD 1 ------------------
// 1. checks if middle is not a peak
// 2. compares elem to neighbors -> peak (local min/max)
// 2*. sets peak in peaks array
// 3. divides

void localextr1(int arr[], int peaks[], int begin, int end){
  int mid = ( begin + end ) / 2 ;

  if ( !peaks[mid] ){
    if ( arr[mid-1] <= arr[mid] && arr[mid] >= arr[mid+1] ){
      printf("Local maximum: %d\n", arr[mid]);
      peaks[mid] = 1;
    }
    if ( arr[mid-1] >= arr[mid] && arr[mid] <= arr[mid+1] ){
      printf("Local minimum: %d\n", arr[mid]);
      peaks[mid] = 1;
    }
  }

  if ( begin != end){
    localextr1(arr, peaks, begin, mid);
    localextr1(arr, peaks, mid+1, end);
  }
}

/// ------------------ METHOD 2 ------------------
// 1. divides until only one elem is between begin - end
// 2. compares elem to neighbors -> peak (local min/max)

// * can be done with a for loop(not really a divide and conquer example)

void localextr2(int arr[], int begin, int end){
  int mid = ( begin + end ) / 2 ;

  if ( begin != end){
    localextr2(arr, begin, mid);
    localextr2(arr, mid+1, end);
  }
  else{
    if ( arr[mid-1] <= arr[mid] && arr[mid] >= arr[mid+1] ){
      printf("Local maximum: %d\n", arr[mid]);
    }
    if ( arr[mid-1] >= arr[mid] && arr[mid] <= arr[mid+1] ){
      printf("Local minimum: %d\n", arr[mid]);
    }
  }
}

/// ------------------ METHOD 3 ------------------
// 1. compares elem to neighbors -> peak (local min/max)
// 2. divides based on the value of mid and its neighbors

// * the greediest out of them (it finds a few solutions)

void localextr3(int arr[], int begin, int end){
  int mid = ( begin + end ) / 2 ;

  if ( arr[mid-1] >= arr[mid] && arr[mid] <= arr[mid+1] ){
      printf("Local minimum: %d\n", arr[mid]);
  }
  else if (arr[mid-1] <= arr[mid] && arr[mid] >= arr[mid+1]){
      printf("Local maximum: %d\n", arr[mid]);
  }
  if (begin!=end){
    if ( arr[mid-1] < arr[mid] ){
      localextr3(arr, begin, mid-1);
    }
    else if ( arr[mid-1] > arr[mid] ){
      localextr3(arr, begin, mid-1);
    }
  }
}

int main(){
  int Arr[SIZE] = { 2 , 7 , 3 , 4 , 1 , 9 , 12 , 6 , 5 , 0 , 7, 3, 5 } ;
  int peaks[SIZE] = {0};

  printf("Method 1:\n");
  localextr1(Arr, peaks, 1, SIZE - 2) ;
  printf("\nMethod 2:\n");
  localextr2(Arr, 1, SIZE - 2) ;
  printf("\nMethod 3:\n");
  localextr3(Arr, 1, SIZE - 2) ; // the begin & end can be tweaked to find different peaks
}
