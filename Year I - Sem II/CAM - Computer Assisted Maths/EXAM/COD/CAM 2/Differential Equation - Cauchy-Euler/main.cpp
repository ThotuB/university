#include <iostream>

using namespace std;

#define A 0
#define B 1

#define STEP 0.1
#define SIZE (unsigned int)((B-A)/STEP) + 1

float x[SIZE] = {A, 0};
float y[SIZE] = {0, 0};
float f_cauchy[SIZE];
float f[SIZE];

float funct(float x, float y){
  return y - x + 2;
}

void print_x_y_f(){
  for (unsigned i = 0 ; i < SIZE ; i++){
    cout<<"x"<<i<<" = "<<x[i]<<"\n";
    cout<<"f = "<<f_cauchy[i]<<"\n";
    cout<<"y"<<i<<" = "<<y[i]<<"\n";
    cout<<"f"<<i<<" = "<<f[i]<<"\n\n";
  }
}

void get_x_y_f(){
  f[0] = funct(x[0], y[0]);
  for (unsigned i = 1 ; i < SIZE ; i++){
    x[i] = x[i-1] + STEP;
    f_cauchy[i] = funct(x[i-1] + 0.5*STEP, y[i-1] + 0.5*STEP*f[i-1]);
    y[i] = y[i-1] + STEP * f_cauchy[i];
    f[i] = funct(x[i], y[i]);
  }
}

int main(){
  get_x_y_f();
  print_x_y_f();

  return 0;
}
