#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 7

#define ROWS 6
#define COLS 7

#define START_X 1
#define START_Y 1
#define START_Z 1

typedef struct _coord {
  unsigned x;
  unsigned y;
  unsigned z;
}coord_t;

coord_t get_coord(unsigned x, unsigned y, unsigned z){
  coord_t newCoord;

  newCoord.x = x;
  newCoord.y = y;
  newCoord.z = z;

  return newCoord;
}

// maze variables
char ***maze;

// path variables
coord_t *pathMin = NULL;
unsigned stepMin = UINT_MAX;

/// ------------------ GETTING FUNCTION ------------------

unsigned is_layer_end(FILE *stream){
  char c = fgetc(stream);
  if ( c == EOF ){
    return 2;
  }
  if ( c == '\n' ){
    return 1;
  }
  ungetc(c, stream);
  return 0;
}

void get_maze(FILE *stream){
  //pathMin = malloc(sizeof())
  maze = (char***)malloc(N * sizeof(char**));

  char c;

  for (unsigned k = 0 ; k < N ; k++){
    maze[k] = (char**)malloc(ROWS * sizeof(char*));
    for (unsigned j = 0 ; j < ROWS ; j++){
      maze[k][j] = (char*)malloc(COLS * sizeof(char));
      for (unsigned i = 0 ; i < COLS ; i++){
        c = fgetc(stream);
        if ( c != '\n' ){
          maze[k][j][i] = c;
        }
        else {
          i--;
        }
      }
    }
  }
}

/// ------------------ PRINTING FUNCTIONS ------------------

void print_maze(){
  for (unsigned i = 0; i < N ; i++){
    for (unsigned j = 0; j < ROWS ; j++){
      for (unsigned k = 0; k < COLS ; k++){
        printf("%c", maze[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void print_path(coord_t *path, unsigned size){
  for (unsigned i = 0; i < size ; i++){
    printf("%u - (%u, %u, %u)\n", i, path[i].y, path[i].z, path[i].x);
  }
}

/// ------------------ PATH FINDING FUNCTIONS ------------------

void copy_coord_array(coord_t *dest, coord_t *src, unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    dest[i] = get_coord(src[i].x, src[i].y, src[i].z);
  }
}

unsigned is_valid(coord_t pos){
  if ( maze[pos.x][pos.y][pos.z] != '.' ){
    return 0;
  }
  return 1;
}

unsigned is_win(coord_t pos){
  if ( pos.x == 0 || pos.y == 0 || pos.z == 0 || pos.x == N-1 || pos.y == N-1 || pos.z == N-1 ){
    return 1;
  }
  return 0;
}

const int dir_x[] = {1, -1, 0, 0, 0, 0};
const int dir_y[] = {0, 0, 1, -1, 0, 0};
const int dir_z[] = {0, 0, 0, 0, 1, -1};
coord_t *path = NULL;

void find_path(coord_t pos, unsigned step){
  path = (coord_t*)realloc(path, step * sizeof(coord_t));

  maze[pos.x][pos.y][pos.z] = 'x';
  path[step-1] = get_coord(pos.x, pos.y, pos.z);

  if ( is_win(pos) ){
    if ( step < stepMin ){
      stepMin = step;

      pathMin = (coord_t*)realloc(pathMin, step * sizeof(coord_t));
      copy_coord_array(pathMin, path, step);
    }
    print_maze();
    print_path(path, step);
  }
  else {
    coord_t nextPos;

    for (unsigned i = 0 ; i < 6 ; i++){
      nextPos = get_coord(pos.x + dir_x[i], pos.y + dir_y[i], pos.z + dir_z[i]);

      if ( is_valid(nextPos) ){
        find_path(nextPos, step + 1);
        maze[nextPos.x][nextPos.y][nextPos.z] = '.';
      }
    }
  }
}

int main(){
  FILE *maze_in = fopen("maze_HW.txt", "r");

  get_maze(maze_in);

  print_maze();

  find_path(get_coord(START_X,START_Y,START_Z), 1);

  printf("\nSHORTEST PATH:\n");

  print_path(pathMin, stepMin);

  return 0;
}
