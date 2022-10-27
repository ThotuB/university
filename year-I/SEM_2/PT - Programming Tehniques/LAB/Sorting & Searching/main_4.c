#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int isPrime(unsigned x){
  if ( x>1 && ( x%2==1 || x==2 ) ){
    for (int i=3 ; i*i <= x ; i += 2){
      if ( x%i == 0){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

void fillArr(unsigned Arr[],int size){
  int k=1;

  if (size>=1){
    Arr[0]=2;
  }
  for (unsigned i=3; k < size && i < UINT_MAX ; i+=2){
    if ( isPrime(i) ){
      Arr[k]=i;
      k++;
    }
  }
}

int binarySearch(unsigned Arr[],unsigned begin,unsigned end,unsigned nr){
  unsigned mid = (begin + end)/2;
  if ( nr < Arr[mid] ){
    return binarySearch(Arr,begin,mid-1,nr);
  }
  else if ( nr > Arr[mid]){
    return binarySearch(Arr,mid+1,end,nr);
  }
  else {
    return mid;
  }
}

int main(){
  unsigned N,X;
  unsigned *primesArr=malloc(0);

  printf("N: ");
  scanf("%u%*[^\n]",&N);

  primesArr=realloc(primesArr,N*sizeof(unsigned));

  fillArr(primesArr, N);
  for (unsigned i=0; i < N ; i++){
    printf("%u ",primesArr[i]);
  }
  printf("\n");

  do {
    printf("X: ");
    scanf("%u%*[^\n]",&X);
    if ( !isPrime(X) ){
      printf("Number is not prime\n");
    }
  }while (!isPrime(X));

  if ( X > primesArr[N-1] ){
    printf("Number is not in array");
  }
  else {
    printf("Number found on position %d(%d)", binarySearch(primesArr,0,N-1,X),binarySearch(primesArr,0,N-1,X)+1);
  }

  return 0;
}
