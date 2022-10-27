#include <stdio.h>
#include <stdlib.h>

long long unsigned find_Hamming_distance(FILE* stream1_in, FILE* stream2_in){
  char c1, c2;
  long long unsigned dist = 0;

  while ( fscanf(stream1_in, "%c", &c1) == 1 && fscanf(stream2_in, "%c", &c2) == 1 ){
    if ( c1 != c2 ){
      dist++;
    }
  }

  return dist;
}

int main(int argc, char *argv[]){
  if ( argc != 3 ){
    fprintf(stderr, "Wrong number of arguments!\n");
    exit(EXIT_FAILURE);
  }

  FILE* hamming1_in = fopen(argv[1], "r");
  FILE* hamming2_in = fopen(argv[2], "r");

  if ( hamming1_in == NULL || hamming2_in == NULL ){
    fprintf(stderr, "File open error!\n");
    exit(EXIT_FAILURE);
  }

  printf("Distance between (%s) & (%s): %llu\n", argv[1], argv[2], find_Hamming_distance(hamming1_in, hamming2_in));

  fclose(hamming1_in);
  fclose(hamming2_in);

  return 0;
}
