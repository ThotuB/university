#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 // SIZE x SIZE table - default: 8
#define QUEENS SIZE

typedef struct _coord {
  unsigned x;
  unsigned y;
}coord_t;

unsigned table[SIZE][SIZE] = {0};
unsigned solutions = 0;

/// ------------------ PRINTING FUNCTIONS ------------------

void print_table(){
  for (unsigned i = 0; i < SIZE ; i++){
    for (unsigned j = 0; j < SIZE ; j++){
      printf("%u   ", table[i][j]);
    }
    printf("\n\n");
  }
  printf("\n");
}

/// ------------------ SVG DRAWING FUNCTIONS ------------------
#define LEN 100

void start_draw(FILE *stream){
  fprintf(stream, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" overflow=\"scroll\">\n", (SIZE + 1) * LEN, 100 * (SIZE + 1) * LEN);
  }

void stop_draw(FILE *stream){
  fprintf(stream, "</svg>");
}

void draw_queen(FILE *stream, unsigned drawing, unsigned i, unsigned j){
  float x = LEN/2 + LEN * j;
  float y = LEN/2 + LEN * i + drawing * (SIZE + 1) * LEN;
  float g = 2.2;

  fprintf(stream, "<g style=\"opacity:1; fill:#ffffff; fill-opacity:0; fill-rule:evenodd; stroke:#000000; stroke-width:3; stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4; stroke-dasharray:none; stroke-opacity:1;\">");
  fprintf(stream, "<circle cx=\"%f\"  cy=\"%f\"  r=\"4\"/>\n", x+g*6,    y+g*12);
  fprintf(stream, "<circle cx=\"%f\"  cy=\"%f\"  r=\"4\"/>\n", x+g*14,   y+g*9);
  fprintf(stream, "<circle cx=\"%f\"  cy=\"%f\"  r=\"4\"/>\n", x+g*22.5, y+g*7.5);
  fprintf(stream, "<circle cx=\"%f\"  cy=\"%f\"  r=\"4\"/>\n", x+g*31,   y+g*9);
  fprintf(stream, "<circle cx=\"%f\"  cy=\"%f\"  r=\"4\"/>\n", x+g*39,   y+g*12);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" />\n", x+g*9, y+g*26, x+g*17.5, y+g*24.5, x+g*30, y+g*24.5, x+g*36, y+g*26);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" />\n", x+g*11.5, y+g*30, x+g*15, y+g*29, x+g*30, y+g*29, x+g*33.5, y+g*30);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" />\n", x+g*12, y+g*33.5, x+g*18, y+g*32.5, x+g*27, y+g*32.5, x+g*33, y+g*33.5);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" />\n", x+g*11, y+g*38.5, x+g*17.5, y+g*39.5, x+g*27.5, y+g*39.5, x+g*34, y+g*38.5);
  fprintf(stream, "<path d=\"M %f,%f L %f,%f L %f,%f\" style=\"fill:none\" />\n", x+g*9, y+g*26, x+g*7, y+g*14, x+g*14.4, y+g*25);
  fprintf(stream, "<path d=\"M %f,%f L %f,%f L %f,%f\" style=\"fill:none\" />\n", x+g*14.4, y+g*25, x+g*14.5, y+g*11, x+g*19.8, y+g*24);
  fprintf(stream, "<path d=\"M %f,%f L %f,%f L %f,%f\" style=\"fill:none\" />\n", x+g*19.8, y+g*24, x+g*22.5, y+g*9.5, x+g*25.2, y+g*24);
  fprintf(stream, "<path d=\"M %f,%f L %f,%f L %f,%f\" style=\"fill:none\" />\n", x+g*25.2, y+g*24, x+g*30.5, y+g*11, x+g*30.6, y+g*25);
  fprintf(stream, "<path d=\"M %f,%f L %f,%f L %f,%f\" style=\"fill:none\" />\n", x+g*30.6, y+g*25, x+g*38, y+g*14, x+g*36, y+g*26);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*9, y+g*26, x+g*9, y+g*28, x+g*10.5, y+g*28, x+g*11.5, y+g*30);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*36, y+g*26, x+g*36, y+g*28, x+g*34.5, y+g*28, x+g*33.5, y+g*30);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*11.5, y+g*30, x+g*12.5, y+g*31.5, x+g*12.5, y+g*31, x+g*12, y+g*33.5);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*33.5, y+g*30, x+g*32.5, y+g*31.5, x+g*32.5, y+g*31, x+g*33, y+g*33.5);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*12, y+g*33.5, x+g*10.5, y+g*34.5, x+g*10.5, y+g*36, x+g*10.5, y+g*36, x+g*9, y+g*37.5, x+g*11, y+g*38.5, x+g*11, y+g*38.5);
  fprintf(stream, "<path d=\"M %f,%f C %f,%f %f,%f  %f,%f C %f,%f %f,%f  %f,%f\" style=\"stroke-linecap:butt;\" />\n", x+g*33, y+g*33.5, x+g*34.5, y+g*34.5, x+g*34.5, y+g*36, x+g*34.5, y+g*36, x+g*36, y+g*37.5, x+g*34, y+g*38.5, x+g*34, y+g*38.5);
  fprintf(stream, "</g>");
}

void draw_table(FILE *stream){
  static unsigned drawing = 0;

  unsigned color[2][3] = {{255, 206, 158},{209, 139, 71}};

  unsigned x, y, r, g, b;

  for (unsigned i = 0 ; i < SIZE ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      x = LEN/2 + j * LEN;
      y = LEN/2 + drawing * (SIZE + 1) * LEN + i * LEN;
      r = color[(i+j)%2][0];
      g = color[(i+j)%2][1];
      b = color[(i+j)%2][2];

      fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" stroke-width=\"1\" stroke=\"rgb(%u,%u,%u)\" fill=\"rgb(%u,%u,%u)\" />\n", x, y, LEN, LEN, r, g, b, r, g, b);
      if ( table[i][j] ){
        draw_queen(stream, drawing, i, j);
      }
    }
  }
  drawing++;
}

/// ------------------ PATH FINDING FUNCTIONS ------------------

unsigned minF(unsigned x, unsigned y){
  return (x < y) ? x : y;
}

unsigned is_valid(unsigned x, unsigned y){
  for (unsigned i = 0 ; i < x ; i++){ // check cols
    if ( table[i][y] == 1 ){
      return 0;
    }
  }
  unsigned offset = minF(x, y);

  for (unsigned i = 0 ; i < offset ; i++){ // check diag 1
    if ( table[i + x - offset][i + y - offset] == 1 ){
      return 0;
    }
  }
  y = SIZE - y - 1;
  offset = minF(x, y);

  for (unsigned i = 0 ; i < offset ; i++){ // check diag 2
    if ( table[i + x - offset][SIZE - (i + y - offset) - 1] == 1 ){
      return 0;
    }
  }

  return 1;
}

void queens_problem(FILE * stream, unsigned queen){
  if ( queen == QUEENS ){
    print_table();
    draw_table(stream);
    solutions++;
  }
  else {
    for (unsigned j = 0 ; j < SIZE ; j++){
      // n-th queen -> placed on n-th row
      // every row has 1 queen
      if ( is_valid(queen, j) ){
        table[queen][j] = 1;
        queens_problem(stream,  queen + 1);
        table[queen][j] = 0;
      }
    }
  }
}

int main(){
  FILE *queens_out = fopen("queens.svg", "w");

  print_table();

  start_draw(queens_out);
  queens_problem(queens_out, 0);
  stop_draw(queens_out);

  printf("Total distinct solutions: %u", solutions);


  return 0;
}
