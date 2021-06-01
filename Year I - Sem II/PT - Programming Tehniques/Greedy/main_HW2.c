#include <stdio.h>

#define SIZE 4

void coin_problem_greedy(unsigned val, unsigned types[SIZE]){
  unsigned coins[SIZE] = {0};
  unsigned coinsTotal = 0;
  int i;

  // calculating coin totals
  for ( i = SIZE - 1; i >= 0 && val != 0; i--){
    if ( types[i] <= val ){
      coins[i] = val/types[i];
      coinsTotal += coins[i];

      val -= coins[i] * types[i];
    }
  }

  // printing coin totals
  printf("\nCoins: %u\n", coinsTotal);
  for ( i = 0 ; i < SIZE ; i++){
    if ( coins[i] != 0 ){
      printf(" ~ %u x %u\n", coins[i], types[i]);
    }
  }
}

int main(){
  unsigned coinTypes[SIZE] = {1, 5, 10, 20}; // to be put in ascending order
  unsigned value;

  printf("Value: ");
  scanf("%u", &value);

  coin_problem_greedy(value, coinTypes);

  return 0;
}
