#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_doubles(double *arr, char *argv[], unsigned size){
  for (unsigned i = 1 ; i <= size ; i++){
    sscanf(argv[i], "%le", &arr[i-1]);
  }
}

void print_doubles(double arr[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
      printf("%le ", arr[i]);
  }
  printf("\n");
}

static int cmpdoubles(const void *p1, const void *p2){
    double dbl1 = *(double*)p1;
    double dbl2 = *(double*)p2;

    if ( dbl1 < dbl2 ){
      return -1;
    }
    else if ( dbl1 == dbl2 ){
      return 0;
    }
    else {
      return 1;
    }
}

int main(int argc, char *argv[]){
    double dbls[argc-1];

    if ( argc < 2 ){
        fprintf(stderr, "Usage: %s <string>...", argv[0]);
        exit(EXIT_FAILURE);
    }

    get_doubles(dbls, argv, argc - 1);

    printf("Before: ");
    print_doubles(dbls, argc-1);

    qsort(&dbls[0], argc - 1, sizeof(double), cmpdoubles);

    printf("After: ");
    print_doubles(dbls, argc-1);

    return 0;
}
