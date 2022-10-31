#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moves = 27; // possible moves at a given moment
const int decisiveMoves = 22; // possible moves after which a winner is possible

/// -------------- TABLE FUNTION(S) --------------

void init_table(int table[3][3][3]){
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      for (int k = 0; k < 3 ; k++){
        table[i][j][k] = 0;
      }
    }
  }
}

void print_table(int table[3][3][3]){
  printf("\n");
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      for (int k = 0; k < 3 ; k++){
        switch ( table[k][i][j] ){
          case 0:printf("- ");break;
          case 1:printf("X ");break;
          case 4:printf("0 ");break;
        }
      }
      printf("\t");
    }
    printf("\n");
  }
  printf("\n");
}

/// -------------- GAME FUNTIONS --------------

int is_valid(int table[3][3][3], char p, int x, int y, int z){
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

void make_move(int table[3][3][3], char c, int x, int y, int z){
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

int check_win(int table[3][3][3], int sum[]){
  if ( moves <= decisiveMoves ){
    for (int i = 0; i < 49; i++){
      if ( sum[i] == 3 || sum[i] == 12){
        return sum[i]/3;
      }
    }
  }
  return 0;
}

/// -------------- SUM FUNTION(S) --------------

void get_sums(int table[3][3][3],int sum[]){
  int cnt = 0;
  int i=0,j=0,k=0,i2=0;
  int* perms[]= {&k, &i, &j, &k, &i, &i, &k, &i, &i2, &k, &i, &i, &i, &i2, &i, &i};

  for (int iter = 0; iter < 14 ; iter++){
    if ( iter == 9 ){
      iter++;
    }
    int *x = perms[iter];
    int *y = perms[iter+1];
    int *z = perms[iter+2];
    for (k = 0 ; k < 3 ; k++){
      for (j = 0; j < 3 ; j++){
        sum[cnt] = 0;
        for (i = 0; i < 3 ; i++){
          i2 = 2 - i;
          sum[cnt] += table[*x][*y][*z];
        }
        if ( iter < 3 || (iter < 9 && j == 0) || (iter < 14 && j==0 && k==0)){
          cnt++;
        }
      }
    }
  }
}

void print_sums(int sum[]){
  for (int cnt = 0 ; cnt < 49 ; cnt++){
    printf("%d ", sum[cnt]);
    if ( (cnt < 27 && ( (cnt + 1) % 3 == 0 || (cnt + 1) % 9 == 0)) || cnt == 35 || cnt == 44 ){
      printf("\n");
    }
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

void dumb_move(int *x, int *y, int *z){
  *x = rand() % 3;
  *y = rand() % 3;
  *z = rand() % 3;
}

/// --------------------------------------------

int main(){
  int Tab[3][3][3];
  int sum[50];

  int winner = 0;
  char player = 'X';
  int x, y, z;

  srand(time(0));

  init_table(Tab);

  while ( !winner ){
    do {
      if ( player == 'X' ){     // player - X
        player_move(&x, &y, &z);
      }
      else {                    // COMP - 0
        dumb_move(&x, &y, &z);
      }
    }while ( !is_valid(Tab, player, x, y, z) );
    if ( player == '0'){
      printf("O moves: %d %d %d\n", x + 1 ,y + 1, z + 1);
    }

    make_move(Tab, player, x, y, z);

    print_table(Tab);

    get_sums(Tab, sum);

    moves--;
    player = change_player(player);
    winner = check_win(Tab,sum);
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
