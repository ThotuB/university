#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define COINS 3 // nr of coins used

unsigned coin_types[] = {1, 10, 5, 25, 100, 75, 50};  // selection of coins
                                                      // first COINS of coin_types are used

uint64_t **get_matrix(unsigned rows, unsigned cols){ // rows x cols matrix of 0s
  uint64_t **arr2d = (uint64_t**)calloc(rows, sizeof(uint64_t*));
  for (uint64_t i = 0 ; i < rows ; i++){
    arr2d[i] = (uint64_t*)calloc(cols, sizeof(uint64_t));
  }

  return arr2d;
}

// void print_matrix(unsigned **arr2d, unsigned rows, unsigned cols){
//   for (unsigned i = 0 ; i < rows ; i++){
//     for (unsigned j = 0 ; j < cols ; j++){
//       printf("%u ", arr2d[i][j]);
//     }
//     printf("\n");
//   }
// }

long long unsigned coin_problem_dynamic(uint64_t **change, int coins, unsigned sum, unsigned value){
  if ( sum == value ){ // value was reached
    return 1;
  }
  if ( sum > value || coins == 0){ // too much money/no more coins to use
    return 0;
  }

  if ( change[sum][coins-1] == 0 ){
    uint64_t way = coin_problem_dynamic(change, coins, sum + coin_types[coins-1], value) + coin_problem_dynamic(change, coins - 1, sum, value);
    change[sum][coins-1] = way;

    return (long long unsigned)way;
  }
  return (long long unsigned)change[sum][coins-1];
}

int main(){
  unsigned value = 132;

  uint64_t **change = get_matrix(value, COINS);
  //print_matrix(change, value+1, COINS);
  printf(" -Ways: %llu\n", coin_problem_dynamic(change, COINS, 0, value));
  //print_matrix(change, value+1, COINS);

  return 0;
}
