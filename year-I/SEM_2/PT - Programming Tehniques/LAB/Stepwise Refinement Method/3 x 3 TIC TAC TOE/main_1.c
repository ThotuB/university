#include <stdio.h>
#include <stdlib.h>

/// -------------- TABLE FUNTION(S) --------------

void init_table(char table[3][3]){
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      table[i][j] = '-';
    }
  }
}

void print_table(char table[3][3]){
  printf("\n");
  for (int i = 0; i < 3 ; i++){
    for (int j = 0; j < 3 ; j++){
      printf("%c ", table[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/// -------------- GAME FUNTIONS --------------

void make_move(char table[3][3], char c, int x, int y){
  table[x][y] = c;
}

char change_player(char p){
  if (p == 'X'){
    return '0';
  }
  return 'X';
}

/// --------------------------------------------

int main(){
  char Tab[3][3];

  init_table(Tab);
  print_table(Tab);

  char player = 'X';
  make_move(Tab, player, 2, 2);
  print_table(Tab);

  player = change_player(player);
  make_move(Tab, player, 1, 2);
  print_table(Tab);

  return 0;
}
