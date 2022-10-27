#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moves = 9; // possible moves at a given moment
const int decisiveMoves = 4; // possible moves after which a winner is possible

/// -------------- TABLE FUNTION(S) --------------

void init_table(int table[3][3]){
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      table[i][j] = 0;
    }
  }
}

void print_table(int table[3][3]){
  printf("\n");
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      switch ( table[i][j] ){
        case 0:printf("- ");break;
        case 1:printf("X ");break;
        case 4:printf("0 ");break;
      }
    }
    printf("\n");
  }
  printf("\n");
}

/// -------------- GAME FUNTIONS --------------

int is_valid(int table[3][3], char p, int x, int y){
  if ( ( x >= 0 && x < 3 ) && ( y >= 0 && y < 3 ) ){
    if ( table[x][y] == 0 ){
      return 1;
    }
  }
  if ( p == 'X'){
    printf("INVALID MOVE\n");
  }
  return 0;
}

void make_move(int table[3][3], char c, int x, int y){
  if (c == 'X'){
    table[x][y] = 1;
  }
  else{
    table[x][y] = 4;
  }
}

char change_player(char p){
  if (p == 'X'){
    return '0';
  }
  return 'X';
}

int check_win(int table[3][3], int sum[]){
  if ( moves <= decisiveMoves ){
    for (int i = 0; i < 8; i++){
      if ( sum[i] == 3 || sum[i] == 12){
        return sum[i]/3;
      }
    }
  }
  return 0;
}

/// -------------- SUM FUNTION(S) --------------

void get_sums(int table[3][3],int sum[]){
  int k = 0;

  // ROWS & COl SUM
  for (int i = 0; i < 3 ; i++){
    sum[k] = 0;
    sum[k+3] = 0;
    for (int j = 0; j < 3 ; j++){
      sum[k] += table[i][j];
      sum[k+3] += table[j][i];
    }
    k++;
  }
  // DIAGS SUM
  k += 3;
  sum[k] = 0;
  for (int i = 0; i < 3 ; i++){
    sum[k] += table[i][i];
  }
  k++;
  sum[k] = 0;
  for (int i = 0; i < 3 ; i++){
    sum[k] += table[i][2 - i];
  }
}

/* void print_sums(int sum[]){
   for (int i = 0; i < 3; i++){
     printf("%d\n", sum[i]);
   }
   printf("\n");
   for (int i = 3; i < 6; i++){
     printf("%d ", sum[i]);
   }
   printf("\n%d %d\n", sum[6], sum[7]);
 }
*/

/// -------------- PLAYER MOVES --------------

void player_move(int *x, int *y){
  printf("X moves: ");
  scanf("%d %d", x, y);
  (*x)--;
  (*y)--;
}

/// -------------- COMPUTER MOVES --------------

int possible_smart_move(int sum[]){
  int iter = -1;
  for (int i = 0; i < 8; i++){
    if ( (sum[i] == 2 && iter == -1) || sum[i] == 8 ){
      iter = i;
    }
  }
  return iter;
}

void dumb_move(int *x, int *y){
  *x = rand() % 3;
  *y = rand() % 3;
}

void big_brain_move(int table[3][3], int *x, int *y, int iter){
  if (iter < 3){          // ROWS
    *x = iter;
    for (int j = 0; j < 3 ; j++){
      if ( table[iter][j] == 0){
        *y = j;
        break;
      }
    }
  }
  else if (iter < 6){     // COLS
    *y = iter - 3;
    for (int i = 0; i < 3 ; i++){
      if ( table[i][iter - 3] == 0){
        *x = i;
        break;
      }
    }

  }
  else if ( iter == 6 ) {  // DIAG I
    for (int i = 0; i < 3 ; i++){
      if ( table[i][i] == 0){
        *x = i;
        *y = i;
        break;
      }
    }
  }
  else {                   // DIAG II
    for (int i = 0; i < 3 ; i++){
      if ( table[i][2 - i] == 0){
        *x = i;
        *y = 2 - i;
        break;
      }
    }
  }
}

void computer_move(int table[3][3], int *x, int *y, int iter){
  if (iter != -1){
    big_brain_move(table,x,y,iter);
  }
  else {
    dumb_move(x, y);
  }
}

/// --------------------------------------------

int main(){
  int Tab[3][3];
  int sum[8];

  int winner = 0;
  char player = 'X';
  int x, y;

  srand(time(0));

  init_table(Tab);

  while ( !winner && moves ){
    do {
      if ( player == 'X' ){     // player - X
        player_move(&x, &y);
      }
      else {                    // COMP - 0
        computer_move(Tab, &x, &y, possible_smart_move(sum) );
      }
    }while ( !is_valid(Tab, player, x, y) );
    if ( player == '0'){
      printf("O moves: %d %d\n", x + 1 ,y + 1);
    }

    make_move(Tab, player, x, y);

    print_table(Tab);

    get_sums(Tab, sum);
    //print_sums(sum);

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
