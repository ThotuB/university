#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moves = 27; // possible moves at a given moment
const int decisiveMoves = 22; // possible moves after which a winner is possible

int table[3][3][3];
int sum[3][50];
/* Rows:
 * 0 -> actual value
 * 1 - 3 -> x, y, z coords (constant values/ mobile pointers)
 */

/// -------------- TABLE FUNTION(S) --------------

void init_table(){
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      for (int k = 0; k < 3 ; k++){
        table[i][j][k] = 0;
      }
    }
  }
}

void print_table(){
  printf("\n");
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      for (int k = 0; k < 3 ; k++){
        switch ( table[k][i][j] ){
          case 0:printf("- ");break;
          case 1:printf("X ");break; // chose 1 & 4 so that
          case 4:printf("0 ");break; // sums don't overlap
        }
      }
      printf("\t");
    }
    printf("\n");
  }
  printf("\n");
}

/// -------------- GAME FUNTIONS --------------

int is_valid(char p, int x, int y, int z){
  if ( ( x >= 0 && x < 3 ) && ( y >= 0 && y < 3 ) && ( z >= 0 && z < 3 ) ){
    if ( table[x][y][z] == 0 ){
      return 1;
    }
  }
  if ( p == 'X'){
    printf("INVALID MOVE\n");
  }
  return 0;
}

void make_move(char c, int x, int y, int z){
  if (c == 'X'){
    table[x][y][z] = 1;
  }
  else{
    table[x][y][z] = 4;
  }
}

char change_player(char p){
  if (p == 'X'){
    return '0';
  }
  return 'X';
}

int check_win(){
  if ( moves <= decisiveMoves ){
    for (int i = 0; i < 49; i++){
      if ( sum[0][i] == 3 || sum[0][i] == 12){
        return sum[0][i]/3;
      }
    }
  }
  return 0;
}

/// -------------- SUM FUNTION(S) --------------

void get_sum_coords(int *ptr, int *i, int *i2, int row, int col){
  if ( ptr == i ){
    sum[row][col] = 10; // *i pointer - mobile
  }
  else if ( ptr == i2){
    sum[row][col] = 20; // *i2 pointer ( 2 - i ) - mobile
  }
  else {
    sum[row][col] = *ptr; // *ptr value - constant
  }
}

void get_sums(){
  int cnt = 0;
  int i=0,j=0,k=0,i2=0;
  int* perms[]= {&k, &i, &j, &k, &i, &i, &k, &i, &i2, &k, &i, &i, &i, &i2, &i, &i}; // "permutations" necessary to get right sums
  //  0 ->  4 : x, y, z lines - faces
  //  3 ->  7 : first diags - faces
  //  6 -> 10 : second diags - faces
  // 10 -> 13 : interior diags

  for (int permCnt = 0; permCnt < 14 ; permCnt++){
    if ( permCnt == 9 ){
      permCnt++;
    }
    int *x = perms[permCnt];
    int *y = perms[permCnt+1];
    int *z = perms[permCnt+2];
    for (k = 0 ; k < 3 ; k++){
      for (j = 0; j < 3 ; j++){
        sum[0][cnt] = 0;
        get_sum_coords(x, &i, &i2, 1, cnt); // gets x - coord value/mobile pointer (sum - row 1)
        get_sum_coords(y, &i, &i2, 2, cnt); // gets y - coord value/mobile pointer (sum - row 2)
        get_sum_coords(z, &i, &i2, 3, cnt); // gets z - coord value/mobile pointer (sum - row 3)
        for (i = 0; i < 3 ; i++){
          i2 = 2 - i;
          sum[0][cnt] += table[*x][*y][*z]; // gets sum value (sum - row 0)
        }
        if ( permCnt < 3 || (permCnt < 9 && j == 0) || (permCnt < 14 && j==0 && k==0)){
          cnt++;
        }
      }
    }
  }
}

void print_sums(){
  for (int cnt = 0 ; cnt < 49 ; cnt++){
    printf("%d ", sum[0][cnt]);
    if ( (cnt < 27 && ( (cnt + 1) % 3 == 0 || (cnt + 1) % 9 == 0)) || cnt == 35 || cnt == 44 ){
      printf("\n");
    }
  }
  printf("\n");
}

void print_full_sums(){
  for (int cnt = 0 ; cnt < 49 ; cnt++){
    //printf("%d - %d %d %d\n", sum[0][cnt], sum[1][cnt], sum[2][cnt], sum[3][cnt]);
  }
  printf("\n");
}

/// -------------- PLAYER MOVES --------------

void player_move(int *x, int *y, int* z){
  printf("X moves: ");
  scanf("%d %d %d", x, y, z);
  (*x)--;
  (*y)--;
  (*z)--;
}

/// -------------- COMPUTER MOVES --------------

int possible_smart_move(){
  int iter = -1;
  for (int i = 0; i < 49; i++){
    if ( (sum[0][i] == 2 && iter == -1) || sum[0][i] == 8 ){ // finds block/ winning possibility ( 2 -> 2 Xs; 8 -> 2 0s)
      iter = i;
    }
  }
  return iter;
}

void get_pointer_or_value(int **ptr, int *i, int *i2, int row, int iter){ // reverse of get_sum_coords
  // sum coords -> mobile pointer ( *i / *i2 ) / coord value
  switch ( sum[row][iter] ){
    case 10: *ptr = i; break;
    case 20: *ptr = i2; break;
    default: **ptr = sum[row][iter]; break;
  }
}

void big_brain_move(int *x, int *y, int *z, int iter){
  int i = 10, i2 = 20;
  int *xx = (int*)malloc(sizeof(int));
  int *yy = (int*)malloc(sizeof(int));
  int *zz = (int*)malloc(sizeof(int));

  get_pointer_or_value(&xx, &i, &i2, 1, iter);
  get_pointer_or_value(&yy, &i, &i2, 2, iter);
  get_pointer_or_value(&zz, &i, &i2, 3, iter);

  for (i = 0 ; i < 3 ; i++){
    i2 = 2 - i;
    if ( table[*xx][*yy][*zz] == 0 ){
      break;
    }
  }

  *x = *xx;
  *y = *yy;
  *z = *zz;
}

void dumb_move(int *x, int *y, int *z){
  *x = rand() % 3;
  *y = rand() % 3;
  *z = rand() % 3;
}

void computer_move(int *x, int *y, int *z, int iter){
  if (iter != -1){
    big_brain_move(x,y,z,iter);
  }
  else {
    dumb_move(x, y, z);
  }
}

/// --------------------------------------------

int main(){
  int winner = 0;
  char player = 'X';
  int x, y, z;

  srand(time(0));

  init_table();

  while ( !winner ){
    do {
      if ( player == 'X' ){     // player - X
        player_move(&x, &y, &z);
      }
      else {                    // COMP - 0
        computer_move(&x, &y, &z, possible_smart_move() );
      }
    }while ( !is_valid(player, x, y, z) );
    if ( player == '0'){
      printf("O moves: %d %d %d\n", x + 1 ,y + 1, z + 1);
    }

    make_move(player, x, y, z);

    print_table();

    get_sums();
    //print_sums();
    print_full_sums();

    moves--;
    player = change_player(player);
    winner = check_win();
  }

  switch ( winner ){
    case 0:
      printf("DRAW...");
      break;
    case 1:
      printf("X WINS!");
      break;
    case 4:
      printf("0 WINS!");
      break;
  }
  return 0;
}
