/*   Given a matrix read from a file and the number of rows and cols, that has walls and free spaces.
 *   Calculate and print the number of possible paths from the upper-left to the lower-right of the matrix,
 * only being allowed to move down and right.
 */

#include <stdio.h>
#include <stdlib.h>

int **mat;
unsigned rows = 0;
unsigned cols = 0;

/// ------------------ GETTING FUNCTION ------------------

int **get_matrix(unsigned r, unsigned c){ // rows x cols matrix of 0s
  int **arr2d = (int**)calloc(r, sizeof(int*));
  for (unsigned i = 0 ; i < r ; i++){
    arr2d[i] = (int*)calloc(c, sizeof(int));
  }

  return arr2d;
}

void get_mat(FILE *stream){
  fscanf(stream, "%u %u", &rows, &cols);

  mat = get_matrix(rows, cols);

  for (unsigned i = 0 ; i < rows ; i++){
    for (unsigned j = 0 ; j < cols ; j++){
      fscanf(stream, "%d", &mat[i][j]);
    }
  }
}

/// ------------------ PRINTING FUNCTIONS ------------------

void print_mat(unsigned r, unsigned c){
  for (unsigned i = 0; i < r ; i++){
    for (unsigned j = 0; j < c ; j++){
      printf("%i\t", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

unsigned add_to_mat(unsigned i, unsigned j, unsigned r, unsigned c){
  if ( i == r || j == c ){
    return 0;
  }
  if ( mat[i][j] == -1 ){
    return 0;
  }
  return mat[i][j];
}

unsigned mat_ways_dynamic(unsigned r, unsigned c){
  mat[r-1][c-1] = 1;

  for (int i = r - 1 ; i >= 0; i--){
    for (int j = c - 1 ; j >= 0 ; j--){
      if ( mat[i][j] != -1 ){
        mat[i][j] += add_to_mat(i+1, j, r, c) + add_to_mat(i, j+1, r, c);
      }
    }
  }

  return mat[0][0];
}

int main(){
  FILE *mat_in = fopen("mat.txt", "r");

  get_mat(mat_in);
  //print_mat(rows, cols);

  printf("Nr of Paths: %u\n", mat_ways_dynamic(rows, cols));

  //print_mat(rows, cols);
  return 0;
}
