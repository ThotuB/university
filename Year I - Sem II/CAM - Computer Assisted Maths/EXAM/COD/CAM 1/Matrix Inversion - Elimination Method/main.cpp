#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

ifstream fin("in.txt");

float A[10][10][10] = {0};
string stepsA[10][10][10];

float D[10][10][10] = {0};
string stepsD[10][10][10];

unsigned n;
float det = 1;

/// ------------------ INITIAL STEP ------------------

void INIT_A_and_D(){
  fin>>n;

  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      fin>>A[0][i][j];
    }
    D[0][i][i] = 1;
  }
}

/// ------------------ PRINTING ------------------

void print_steps(){
  for (unsigned k = 0 ; k <= n ; k++){
    cout<<"STEP "<<k<<":\t";
    for (unsigned i = 1 ; i <= n ; i++){
      for (unsigned j = 1 ; j <= n ; j++){
        cout<<A[k][i][j]<<"\t";
      }
      cout<<"  |\t";
      for (unsigned j = 1 ; j <= n ; j++){
        cout<<D[k][i][j]<<"\t";
      }
      cout<<"\n\t";
    }
    cout<<'\n';
  }
}

void print_matrix(float mat[10][10][10], char m, unsigned index, int i){
  cout<<m<<i<<" =\t";
  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      cout<<mat[index][i][j]<<"\t";
    }
    cout<<"\n\t";
  }
  cout<<"\n";
}

void print_matrix(string mat[10][10][10], char m, unsigned index, int i){
  cout<<m<<i<<" =\t";
  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      cout<<mat[index][i][j]<<"\t";
    }
    cout<<"\n\t";
  }
  cout<<"\n";
}

/// ------------------ NEXT STEPS ------------------

void get_A_and_D(unsigned k){
  // A matrix
  for (unsigned j = k + 1; j <= n ; j++){
    A[k][k][j] = A[k-1][k][j] / A[k-1][k][k];
    stepsA[k][k][j] = to_string(A[k-1][k][j]) + "/" + to_string(A[k-1][k][k]) + " = " + to_string(A[k][k][j]);
  }
  for (unsigned i = 1; i <= k ; i++){
    A[k][i][i] = 1;
    stepsA[k][i][i] = "1";
  }
  for (unsigned i = 1; i <= n ; i++){
    for (unsigned j = k + 1; j <= n ; j++){
      if ( i != k ){
        A[k][i][j] = A[k-1][i][j] - A[k-1][i][k] * A[k][k][j];
        stepsA[k][i][j] = to_string(A[k-1][i][j]) + " - " + to_string(A[k-1][i][k]) + " * " + to_string(A[k][k][j]) + " = " + to_string(A[k][i][j]);;
      }
    }
  }
  for (unsigned i = 1; i <= n ; i++){
    for (unsigned j = 1; j <= k ; j++){
      if ( i != j ){
        A[k][i][j] = 0;
        stepsA[k][i][j] = "0";
      }
    }
  }

  // D matrix
  for (unsigned j = 1; j <= k ; j++){
    D[k][k][j] = D[k-1][k][j] / A[k-1][k][k];
    stepsD[k][k][j] = to_string(D[k-1][k][j]) + "/" + to_string(A[k-1][k][k]) + " = " + to_string(D[k][k][j]);;
  }
  for (unsigned i = k + 1; i <= n ; i++){
    D[k][i][i] = 1;
    stepsD[k][i][i] = "1";
  }
  for (unsigned i = 1; i <= n ; i++){
    for (unsigned j = 1; j <= k ; j++){
      if ( i != k ){
        D[k][i][j] = D[k-1][i][j] - A[k-1][i][k] * D[k][k][j];
        stepsD[k][i][j] = to_string(D[k-1][i][j]) + " - " + to_string(A[k-1][i][k]) + " * " + to_string(D[k][k][j]) + " = " + to_string(D[k][i][j]);;
      }
    }
  }
  for (unsigned i = 1; i <= n ; i++){
    for (unsigned j = k + 1; j <= n ; j++){
      if ( i != j ){
        D[k][i][j] = 0;
        stepsD[k][i][j] = "0";
      }
    }
  }
}

int main(){
  INIT_A_and_D();

  for (unsigned k = 1; k <= n ; k++){
    get_A_and_D(k);
    det *= A[k-1][k][k];
  }

  cout<<fixed<<setprecision(3);

  // for (unsigned k = 0; k <= n ; k++){
  //   print_matrix(A,'A', k, k);
  //   print_matrix(D,'D', k, k);
  // }

  print_steps();

  cout<<"Results:\n";
  print_matrix(D, 'A', n, -1);
  cout<<"Det: "<<det<<'\n';
  return 0;
}
