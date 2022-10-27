#include <stdio.h>
#include <stdlib.h>

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
  for (int i = 0; i < 8; i++){
    if ( sum[i] == 3 || sum[i] == 12){
      return sum[i]/3;
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

/// -------------- PLAYER MOVES --------------

void player_move(int *x, int *y, char p){
  printf("%c moves: ", p);
  scanf("%d %d", x, y);
  (*x)--;
  (*y)--;
}

/// --------------------------------------------

int main(){
  int Tab[3][3];
  int sum[8];

  int winner = 0;
  char player = 'X';
  int x, y;

  init_table(Tab);

  while ( !winner ){
    player_move(&x, &y, player);

    make_move(Tab, player, x, y);

    print_table(Tab);

    get_sums(Tab, sum);

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
