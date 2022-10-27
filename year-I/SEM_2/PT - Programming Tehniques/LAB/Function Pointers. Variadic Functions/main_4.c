#include <stdio.h>
#include <math.h>
#include <string.h>

#define FUNC_SIZE 7

int main(){
  double (*math_functions[FUNC_SIZE])(double) = {&sin, &cos, &ceil, &floor, &fabs, &log, &sqrt};
  char menu[FUNC_SIZE][6] = {"sin", "cos", "ceil", "floor", "fabs", "log", "sqrt"};
  char option[6];
  double nr;

  printf("Using 'STOP' for function stops program!\n");
  while (1){
    printf("Function: ");
    scanf("%6s", option);

    if ( strcasecmp(option, "STOP") == 0 ){
      break;
    }

    printf("Number: ");
    scanf("%lf", &nr);

    for (unsigned i = 0 ; i < FUNC_SIZE ; i++){
      if ( strcmp(option, menu[i]) == 0 ){
        printf("\nAnswer: %lf\n\n", math_functions[i](nr));
      }
    }
  }
}
