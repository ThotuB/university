#include <stdio.h>

#define LENGTH 8

unsigned prices[LENGTH] = {1, 4, 5, 6, 10, 11, 14, 15};

unsigned best_price(unsigned length){
  for (unsigned i = 1 ; i < length ; i++){
    for (unsigned j = 0 ; j < (i+1)/2 ; j++){
      unsigned priceTry = prices[j] + prices[i-j-1];
      if ( prices[i] < priceTry ){
        prices[i] = priceTry;
      }
    }
  }

  return prices[length-1];
}

void print_prices(){
  printf("Prices: ");
  for (unsigned i = 0 ; i < LENGTH ; i++){
    printf("%u ", prices[i]);
  }
  printf("\n");
}

int main(){
  printf("Best Price: %u\n", best_price(LENGTH));
  print_prices();
  return 0;
}
