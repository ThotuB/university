#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

ifstream fin("in.txt");

float A[10][10];
float B[10][10][10] = {0};

float coefs[10] = {0};
unsigned n;

/// ------------------ INITIAL STEP ------------------

void INIT_A_B_coefs(){
  fin>>n;

  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      fin>>A[i][j];
      B[1][i][j] = A[i][j];
    }
  }
  coefs[1] = 1;
}

/// ------------------ PRINTING ------------------

void print_steps(){
  for (unsigned k = 1 ; k <= n ; k++){
    cout<<"STEP "<<k<<'\n';
    cout<<"\tc"<<k<<" = "<<coefs[k]<<'\n';
  }
}

/// ------------------ MATRIX FUNCTIONS ------------------

float trace(unsigned k){
  float sum = 0;
  for (unsigned i = 1 ; i <= n ; i++){
    sum += B[k][i][i];
  }
  return sum;
}

void copy_mat(float dest[10][10], float **src){
  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      dest[i][j] = src[i][j];
    }
  }
}

float **scalar_mat_mult(float c, float **mat){
  for (unsigned i = 1 ; i <= n ; i++){
    for (unsigned j = 1 ; j <= n ; j++){
      mat[i][j] *= c;
    }
  }
  return mat;
}

// float **mat_add(float mat1[10][10], **mat2){
//   float **sum = (float**)
// }

/// ------------------ NEXT STEPS ------------------

void get_coefs_B(unsigned k){
  coefs[k] = -(1/(k-1)) * trace(k-1);


}

int main(){
  cout<<fixed<<setprecision(3);

  for (unsigned k = 2 ; k <= n ; k++){
    get_coefs_B(k);
  }

  print_steps();

  return 0;
}
