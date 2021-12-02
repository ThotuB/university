#include <stdio.h>
#include <stdarg.h>
#include <float.h>

void print_min_max(unsigned int n,... ){
  va_list argList;
  va_start(argList, n);

  float nr;
  float max = FLT_MIN;
  float min = FLT_MAX;

  for (unsigned i = 0 ; i < n ; i++){
    nr = va_arg(argList, double);
    if ( nr < min ){
      min = nr;
    }
    if ( nr > max ){
      max = nr;
    }
  }
  va_end(argList);

  printf("-Max: %f\n", max);
  printf("-Min: %f\n", min);
}

int main(){
  print_min_max(10, -2.0, 7.43, 3.343, 12.23, -9.646, 5.15, 34.423, -1.436, 9.21, 22.86);
  return 0;
}
