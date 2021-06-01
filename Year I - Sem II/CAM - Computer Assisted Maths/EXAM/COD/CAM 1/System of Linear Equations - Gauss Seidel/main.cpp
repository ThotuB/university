#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

ifstream fin("in.txt");

#define ITER_MAX 100
#define EPS 0.01

float A[10][10] = {0};
float X[ITER_MAX][10] = {0};
float B[10] = {0};

string sums_string[10];
unsigned n;

/// ------------------ INITIAL STEP ------------------

void INIT_matrix(){
  fin>>n;

  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      fin >> A[i][j];
      if ( j < i ){
        sums_string[i] += to_string(-A[i][j]) + "x" + to_string(j) + "(k)"  + " + ";
      }
      if ( j > i ){
        sums_string[i] += to_string(-A[i][j]) + "x" + to_string(j) + "(k-1)" + " + ";
      }
    }
    fin >> B[i];
    X[0][i] = B[i]/A[i][i];
  }
}

/// ------------------ PRINTING ------------------

void print_matrix(float mat[10][10], char m){
  cout<<m<<" =\t";
  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      cout<<mat[i][j]<<"\t";
    }
    cout<<"\n\t";
  }
  cout<<"\n";
}

void print_steps(unsigned step_max){
  for (unsigned k = 0 ; k < step_max ; k++){
    cout<<"STEP "<<k<<":\n";
    for (unsigned i = 1 ; i <= n ; i++){
      cout<<"\tX"<<i<<"("<<k<<") = "<<X[k][i]<<"\n";
    }
    cout<<"\n";
    if ( k > 0 ){
      for (unsigned i = 1 ; i <= n ; i++){
        cout<<"\t|X"<<i<<"("<<k<<")"<<" - X"<<i<<"("<<k-1<<")"<<"| = "<<"|"<<X[k][i]<<" - "<<X[k-1][i]<<"| = "<<fabs(X[k][i] - X[k-1][i])<<'\n';
      }
      cout<<"\n";
    }
  }
  cout<<"\n";
}

void print_sums_string(){
  for (unsigned i = 1 ; i <= n ; i++){
    cout<<sums_string[i]<<"\n";
  }
}

/// ------------------ NEXT STEPS ------------------

bool stop_cond(unsigned k){
  if ( k == 0 ){
    return 0;
  }
  for (unsigned i = 1 ; i <= n ; i++){
    if ( fabs(X[k][i] - X[k-1][i]) > EPS ){
      return 0;
    }
  }
  return 1;
}

float sum(unsigned j, unsigned j_stop, unsigned i, unsigned k){
  float sum = 0;
  for ( ; j <= j_stop ; j++){
    sum += A[i][j]*X[k][j];
    cout<<-A[i][j]<<"*"<<X[k][j]<<" ";
  }
  return sum;
}

void get_X(unsigned k){
  for (unsigned i = 1 ; i <= n ; i++){
    cout<<"1/"<<A[i][i]<<" * ("<<B[i]<<" ";
    X[k][i] = (1/A[i][i])*(B[i] - sum(1, i-1, i, k) - sum(i+1, n, i, k-1));
    cout<<") = "<<X[k][i]<<"\n";
  }
  cout<<"\n";
}

int main(){
  cout<<fixed<<setprecision(3);
  unsigned k;

  INIT_matrix();
  print_matrix(A, 'A');
  print_sums_string();

  for (k = 1; !stop_cond(k-1) && k < ITER_MAX ; k++){
    get_X(k);
  }

  print_steps(k);

  return 0;
}
