#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

#define MAX_ITER 1000

#define EPS_X 0.0001
#define EPS_F 0.0001

#define A 1
#define B 2

double f(double x){
  return x*x*x - x - 2;
}

double bisection_method(){
  double left[MAX_ITER], right[MAX_ITER], mid[MAX_ITER];
  unsigned iter;
  left[0] = A;
  right[0] = B;

  if ( f(left[0]) * f(right[0]) > 0 ){
    cout<<"WRONG INTERVAL";
  }
  else {
    for (iter = 1 ; iter < MAX_ITER ; iter++){
      mid[iter] = (left[iter-1] + right[iter-1])/2;
      cout<< f(mid[iter])<< "\n";

      if ( f(mid[iter]) * f(right[iter-1]) < 0 ){ // f(mid) * f(right) < 0
        left[iter] = mid[iter];
        right[iter] = right[iter-1];
      }
      else if ( f(left[iter-1]) * f(mid[iter]) < 0 ){ // f(left) * f(mid) < 0
        right[iter] = mid[iter];
        left[iter] = left[iter-1];
      }
      else { // f(mid) = 0
        break;
      }

      if ( fabs(f(mid[iter])) <= EPS_F && fabs(right[iter] - left[iter]) <= EPS_X ){
        break;
      }
    }
  }

  cout << "Solution (iter "<<iter<<"): f( "<<mid[iter]<<" ) ~= 0";
  return  mid[iter];
}

int main(){
  bisection_method();
}
