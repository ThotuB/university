#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_doubles(char *arr[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
      printf("%s ", arr[i]);
  }
  printf("\n");
}

double get_double(char *str){
  unsigned i;
  int nr_sgn, exp_sgn, nr = 0, exp = 0;
  unsigned size = 0;

  // number/mantissa sign
  nr_sgn = ( str[0] == '-' ) ? -1 : 1;
  // exponent sign
  exp_sgn = ( *(strchr(str, 'e')+1) == '-' ) ? -1 : 1;
  // nubmer/mantissa
  if ( nr_sgn == -1 ) str++;

  for (i = 0 ; str[i] != 'e' ; i++){
    if ( i == 1 ){
      continue;
    }
    nr = nr*10 + (str[i]-'0');
    size++;
  }
  size--;
  // exponent
  for (i += 2 ; str[i] != '\0' ; i++){
    exp = exp*10 + (str[i]-'0');
  }
  // double
  double dbl = nr;
  for (unsigned i = 0 ; i < exp + (-exp_sgn * size) ; i++){
    dbl *= pow(10, exp_sgn);
  }
  dbl *= nr_sgn;

  return dbl;
}

static int cmpstringptr(const void *p1, const void *p2){
    char *str1 = *(char**)p1;
    char *str2 = *(char**)p2;

    //printf("%s - %s\n", str1, str2);

    double nr1 = get_double(str1);
    double nr2 = get_double(str2);

    //printf("%e - %e\n\n", nr1, nr2);

    if ( nr1 < nr2 ){
      return -1;
    }
    else if ( nr1 == nr2){
      return 0;
    }
    else {
      return 1;
    }
}

int main(int argc, char *argv[]){
    if ( argc < 2 ){
        fprintf(stderr, "Usage: %s <string>...", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Before: ");
    print_doubles(argv+1, argc-1);

    qsort(&argv[1], argc-1, sizeof(char*), cmpstringptr);

    printf("After: ");
    print_doubles(argv+1, argc-1);

    return 0;
}
