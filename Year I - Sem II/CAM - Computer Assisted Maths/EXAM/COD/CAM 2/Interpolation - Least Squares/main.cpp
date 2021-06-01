#include <iostream>
#include <math.h>

using namespace std;

#define SIZE 5
#define ORDER 2
#define SIZE_V 2

float x[SIZE] = {0, 2, 4, 6, 8};
float y[SIZE] = {5.2, 8, 10.4, 12.4, 14};

float xv[SIZE_V] = {1.5, 3.9};
float yv[SIZE_V] = {0};

float sum[2*ORDER+1] = {0};
float t[ORDER+1] = {0};

float poly_coefs[ORDER+1] = {0};

/// ------------------ PRINTING ------------------

void print_sum(){
  cout<<"Sum:\n";
  for (unsigned i = 0 ; i < 2*ORDER + 1 ; i++){
    printf("%.3f\t", sum[i]);
  }
  cout<<"\n\n";
}

void print_t(){
  cout<<"t:\n";
  for (unsigned i = 0 ; i < ORDER + 1 ; i++){
    printf("%.3f\t", t[i]);
  }
  printf("\n\n");
}

void print_system(){
  cout<<"System:\n";
  for (unsigned i = 0 ; i < ORDER + 1 ; i++){
    for (unsigned j = 0 ; j < ORDER + 1 ; j++){
      printf("%.3f * a%u", sum[j+i], j);
      if ( j < ORDER ){
        cout<<"\t+\t";
      }
    }
    printf("\t=\t%.3f\n", t[i]);
  }
  cout<<"\n";
}

void print_poly(){
  cout<<"P"<<ORDER<<"(x) = ";
  for (unsigned i = 0 ; i < ORDER + 1 ; i++){
    printf("%.3f * x^%u", poly_coefs[i], i);
    if ( i < ORDER ){
      cout<<"\t+\t";
    }
  }
  cout<<"\n\n";
}

void print_yv(){
  cout<<"yv:\n";
  for (unsigned i = 0 ; i < SIZE_V ; i++){
    printf("%.3f\t", yv[i]);
  }
  cout<<"\n\n";
}

/// ------------------------------------------

void get_sum(){
  for (unsigned i = 0 ; i < 2*ORDER + 1 ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      sum[i] += pow(x[j], i);
    }
  }
}

void get_t(){
  for (unsigned i = 0 ; i < ORDER + 1 ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      t[i] += pow(x[j], i) * y[j];
    }
  }
}

float det(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33){
  return a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a13*a22*a31 - a11*a23*a32 - a12*a21*a33;
}

void get_poly_coefs(){
  poly_coefs[0] = det(t[0], sum[1], sum[2], t[1], sum[2], sum[3], t[2], sum[3], sum[4])/det(sum[0], sum[1], sum[2], sum[1], sum[2], sum[3], sum[2], sum[3], sum[4]);
  poly_coefs[1] = det(sum[0], t[0], sum[2], sum[1], t[1], sum[3], sum[2], t[2], sum[4])/det(sum[0], sum[1], sum[2], sum[1], sum[2], sum[3], sum[2], sum[3], sum[4]);
  poly_coefs[2] = det(sum[0], sum[1], t[0], sum[1], sum[2], t[1], sum[2], sum[3], t[2])/det(sum[0], sum[1], sum[2], sum[1], sum[2], sum[3], sum[2], sum[3], sum[4]);
}

void get_yv(){
  for (unsigned i = 0 ; i < SIZE_V ; i++){
    for (unsigned j = 0 ; j < ORDER + 1 ; j++){
      yv[i] += poly_coefs[j] * pow(xv[i], j);
    }
  }
}

int main(){
  get_sum();
  print_sum();

  get_t();
  print_t();

  print_system();

  get_poly_coefs();
  print_poly();

  get_yv();
  print_yv();
  return 0;
}
