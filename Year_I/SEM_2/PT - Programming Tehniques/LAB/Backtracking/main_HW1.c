#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define START_X 1
#define START_Y 1

typedef struct _coord {
  unsigned x;
  unsigned y;
}coord_t;

// maze variables
char **maze;
unsigned rows = 1;
unsigned cols = 1;

// path variables
coord_t *pathMin = NULL;
unsigned stepMin = UINT_MAX;

/// ------------------ GETTING FUNCTION ------------------

void get_maze(FILE *stream){
  //pathMin = malloc(sizeof())
  maze = (char**)malloc(sizeof(char*));
  maze[0] = (char*)malloc(sizeof(char));

  char c;
  unsigned i = 0, j = 0;

  for (c = fgetc(stream) ; c != EOF ; c = fgetc(stream) ){
    if ( c == '\n' ){ // row end
      rows++;
      maze = (char**)realloc(maze, rows * sizeof(char*));
      maze[rows-1] = (char*)malloc((cols - 1) * sizeof(char));

      i++; j = 0;
    }
    else {
      if ( rows == 1 ){
        maze[0] = (char*)realloc(maze[0], cols * sizeof(char));
        cols++;
      }

      maze[i][j] = c;
      j++;
    }
  }
  rows--;cols--;
}

/// ------------------ PRINTING FUNCTIONS ------------------

void print_maze(unsigned rows, unsigned cols){
  for (unsigned i = 0; i < rows ; i++){
    for (unsigned j = 0; j < cols ; j++){
      printf("%c", maze[i][j]);
    }
    printf("\n");
  }
}

void print_path(coord_t *path, unsigned size){
  for (unsigned i = 0; i < size ; i++){
    printf("%u - (%u, %u)\n", i, path[i].x, path[i].y);
  }
  printf("\n");
}

/// ------------------ PATH FINDING FUNCTIONS ------------------

void copy_coord_array(coord_t *dest, coord_t *src, unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    dest[i].x = src[i].x;
    dest[i].y = src[i].y;
  }
}

unsigned is_valid(unsigned x, unsigned y){
  if ( maze[x][y] != '.' ){
    return 0;
  }
  return 1;
}

unsigned is_win(unsigned x, unsigned y){
  if ( x == 0 || y == 0 || x == rows-1 || y == cols-1 ){
    return 1;
  }
  return 0;
}

const int dir_x[] = {1, -1, 0, 0};
const int dir_y[] = {0, 0, 1, -1};
coord_t *path = NULL;

void find_path(unsigned x, unsigned y, unsigned step){
  path = (coord_t*)realloc(path, step * sizeof(coord_t));

  maze[x][y] = 'x';
  path[step-1].x = x;
  path[step-1].y = y;

  if ( is_win(x, y) ){
    if ( step < stepMin ){
      stepMin = step;

      pathMin = (coord_t*)realloc(pathMin, step * sizeof(coord_t));
      copy_coord_array(pathMin, path, step);
    }
    print_maze(rows, cols);
    print_path(path, step);
  }
  else {
    unsigned nextX;
    unsigned nextY;

    for (unsigned i = 0 ; i < 4 ; i++){
      nextX = x + dir_x[i];
      nextY = y + dir_y[i];

      if ( is_valid(nextX, nextY) ){
        find_path(nextX, nextY, step + 1);
        maze[nextX][nextY] = '.';
      }
    }
  }
}

int main(){
  FILE *maze_in = fopen("maze.txt", "r");

  get_maze(maze_in);

  //print_maze(rows, cols);

  find_path(START_X, START_Y, 1);

  printf("\nSHORTEST PATH:\n");

  print_path(pathMin, stepMin);

  return 0;
}
