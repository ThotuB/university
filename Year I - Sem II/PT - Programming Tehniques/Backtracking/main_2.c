#include <stdio.h>
#include <stdlib.h>

#define SIZE 6 // base size: 8 ( chess board )

#define LENGTH 100 // svg: distance between squares

#define INIT_X 0 // start coord X
#define INIT_Y 0 // start coord Y

typedef struct coord{
  int x;
  int y;
}coord_t;

unsigned table[SIZE][SIZE] = {0};
coord_t path[SIZE*SIZE];

coord_t get_coord(int x, int y){
  coord_t coord;

  coord.x = x;
  coord.y = y;

  return coord;
}

/// -------------- PRINTING FUNCTION --------------

void print_table(){
  for (unsigned i = 0 ; i < SIZE ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      printf("%u\t", table[i][j]);
    }
    printf("\n\n\n");
  }
}

void draw_knight(FILE *stream){
  fprintf(stream, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%u\" height=\"%u\" version=\"1.1\" overflow=\"scroll\">\n", SIZE * LENGTH, SIZE * LENGTH);

  // draw table
  for (unsigned i = 0 ; i < SIZE; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" stroke=\"black\" fill=\"white\" stroke-width=\"1\" />\n", i*LENGTH, j*LENGTH, LENGTH, LENGTH);
    }
  }

  // draw steps
  unsigned x1, y1, x2, y2;
  float color = 0;

  for (unsigned i = 0 ; i < SIZE*SIZE - 1 ; i++){
    x1 = path[i].x * LENGTH + LENGTH/2;
    y1 = path[i].y * LENGTH + LENGTH/2;
    x2 = path[i+1].x * LENGTH + LENGTH/2;
    y2 = path[i+1].y * LENGTH + LENGTH/2;

    fprintf(stream, "<line x1=\"%u\" y1=\"%u\" x2=\"%u\" y2=\"%u\" stroke=\"rgb(%f, 0, %f)\" stroke-width=\"4\" />\n", x1, y1, x2, y2, color, 255 - color);
    color += 255/(SIZE*SIZE);
  }

  fprintf(stream, "</svg>");
}

/// -------------- PATH FINDING FUNCTIONS --------------

unsigned valid_pos(coord_t pos){
  if ( pos.x < 0 || pos.y < 0 || pos.x >= SIZE || pos.y >= SIZE){
    return 0;
  }
  if ( table[pos.y][pos.x] != 0 ){
    return 0;
  }
  return 1;
}

int solFound = 0;

// move permutations
static int dir_X[] = { 1, 2, 2, 1, -1, -2, -2, -1};
static int dir_Y[] = { 2, 1, -1, -2, -2, -1, 1, 2};

void knight_problem_recursive(coord_t pos, unsigned step){
  table[pos.y][pos.x] = step;
  path[step-1] = get_coord(pos.x, pos.y);

  if ( step == SIZE * SIZE ){ // would be more efficient to exit() after sol is found - wanted to make an svg
    solFound = 1;
  }
  else {
    coord_t newPos;

    // trying 8 knight moves
    for (unsigned i = 0 ; i < 8 && !solFound ; i++){
      newPos.x = pos.x + dir_X[i];
      newPos.y = pos.y + dir_Y[i];

      if ( valid_pos(newPos) ){ // validating move
        //printf("%u", step);
        knight_problem_recursive(newPos, step + 1);
        if ( !solFound ) {
            table[newPos.y][newPos.x] = 0;
        }
      }
    }
  }
}

void knight_problem_iterative(coord_t pos){
  unsigned step = 0;
  unsigned moves[SIZE*SIZE] = {0};

  coord_t newPos = pos;

  while ( step != SIZE*SIZE - 1 && moves[0] != 8 ){
    path[step] = pos;
    table[pos.y][pos.x] = step + 1;

    for ( ; moves[step] < 8 ; moves[step]++){
      newPos.x = pos.x + dir_X[moves[step]];
      newPos.y = pos.y + dir_Y[moves[step]];

      if ( valid_pos(newPos) ){ // validating move
        break;
      }
    }

    if ( moves[step] == 8 ){ // if no path found
      // moves & table at step are reset
      moves[step] = 0;
      table[pos.y][pos.x] = 0;

      // position becomes anterior position
      pos = path[step-1];
      moves[step-1]++;

      step--;
    }
    else { // if path found
      pos = newPos; // position change

      step++;
    }

  }

  if ( moves[0] != 8){
    solFound = 1;
    path[step] = pos;
    table[pos.y][pos.x] = step + 1;
  }
}

int main(){
  unsigned option = 1;
  print_table();

  printf("* Choose one:\n");
  printf("0 -> Recursive\n");
  printf("1 -> Iterative\n");
  printf("Option: ");
  scanf("%u", &option);

  switch( option ){
    case 0: knight_problem_recursive( get_coord(INIT_X, INIT_Y), 1); break;
    case 1: knight_problem_iterative( get_coord(INIT_X, INIT_Y) ); break;
    default: return 0;
  }

  if ( solFound ){
    print_table();
  }
  else{
    printf("No solution found!");
  }

  FILE *knight_out = fopen("knight.svg", "w");

  draw_knight(knight_out);
  return 0;
}
