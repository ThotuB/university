#include <stdio.h>
#include <stdlib.h>

unsigned *fibArr;

unsigned fibonacci_dynamic(unsigned n){
  if ( n > 1){
    if (  fibArr[n] == 0 ){
      unsigned sum = fibonacci_dynamic(n-2) + fibonacci_dynamic(n-1);
      fibArr[n] = sum;
      //cout<<sum<<" ";
      return sum;
    }
    return fibArr[n];
  }
  return n;
}

int main(){
  unsigned n;

  printf("n: ");
  scanf("%u", &n);

  fibArr = (unsigned*)calloc(n + 1, sizeof(unsigned));

  printf("Fibonacci [%u] = %u\n", n, fibonacci_dynamic(n));

  return 0;
}
