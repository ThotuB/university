#include <iostream>

using namespace std;

#define SIZE 5
#define ORDER 2
#define SIZE_V 2

float x[SIZE] = {0, 2, 4, 6, 8};
float y[SIZE] = {5.2, 8, 10.4, 12.4, 14};

float xv[SIZE_V] = {1.5, 3.9};
float yv[SIZE_V] = {0};

float delta_y[SIZE][SIZE] = {0};
float poly_coefs[SIZE];

float q[SIZE_V][SIZE];

/// ------------------ PRINTING ------------------

void print_delta_y(){
  cout<<"Delta Y:\n";
  for (unsigned i = 0 ; i < SIZE ; i++){
    for (unsigned j = 0 ; j < SIZE - i ; j++){
      printf("%.3f\t", delta_y[i][j]);
    }
    cout<<"\n";
  }
  cout<<"\n";
}

void print_poly_coefs(){
  cout<<"P"<<ORDER<<"(q):\n";
  for (unsigned j = 0 ; j < SIZE ; j++){
    printf("%.3f\t", poly_coefs[j]);
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

void print_q(){
  cout<<"q:\n";
  for (unsigned i = 0 ; i < SIZE_V ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      printf("%.3f\t", q[i][j]);
    }
    cout<<"\n";
  }
  cout<<"\n";
}

/// ------------------------------------------

void get_delta_y(){
  for (unsigned j = 0 ; j < SIZE ; j++){
    for (unsigned i = 0 ; i < SIZE - j ; i++){
      if ( j == 0 ){
        delta_y[i][j] = y[i];
      }
      else {
        delta_y[i][j] = delta_y[i+1][j-1] - delta_y[i][j-1];
      }
    }
  }
}

unsigned factorial(unsigned f){
  if ( f == 0 ){
    return 1;
  }
  return f * factorial(f-1);
}

void get_poly_coefs(){
  for (unsigned i = 0 ; i <= ORDER ; i++){
    poly_coefs[i] = delta_y[0][i] / factorial(i);
  }
}

void get_q(){
  for (unsigned i = 0 ; i < SIZE_V ; i++){
    q[i][0] = 1;
    for (unsigned j = 1 ; j < SIZE ; j++){
      q[i][j] = q[i][j-1] * (xv[i] - x[j-1]);
    }
  }
}

void get_yv(){
  for (unsigned i = 0 ; i < SIZE_V ; i++){
    for (unsigned j = 0 ; j <= ORDER ; j++){
      yv[i] += poly_coefs[j] * q[i][j];
    }
  }

}


int main(){
  get_delta_y();
  print_delta_y();

  get_poly_coefs();
  get_q();
  get_yv();

  print_poly_coefs();
  print_q();
  print_yv();

  return 0;
}
