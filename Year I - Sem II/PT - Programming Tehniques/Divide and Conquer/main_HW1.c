#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITER 5  // no of iterations

#define WIDTH 1920 // width
#define HEIGHT 1080 // height

#define CENTER_X WIDTH/2
#define CENTER_Y HEIGHT/2

#define LENGTH 1000

double PI = acos(-1);

typedef struct _point{
  double x;
  double y;
}point_t;

/// ------------------ HEADER & FOOTER OUTPUT ------------------

void output_header(FILE *stream){
  fprintf(stream, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%u\" height=\"%u\" version=\"1.1\" overflow=\"scroll\">\n", CENTER_X + LENGTH/2, CENTER_Y + LENGTH/2);
}

void output_footer(FILE *stream){
  fprintf(stream, "</svg>");
}

/// ------------------ DRAWING FUNCTIONS ------------------

void draw_square(FILE *stream, point_t center, double length, unsigned color){
  double x = CENTER_X + center.x - length/2;
  double y = CENTER_Y - center.y - length/2;

  fprintf(stream, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"rgb(%u,%u,%u)\" stroke=\"rgb(%u,%u,%u)\" stroke-width=\"1\" />\n", x, y, length, length, color, color, color, color, color, color);
}

/// ------------------ GETTING FUNCTIONS ------------------

point_t get_point(double x, double y){
  point_t point;

  point.x = x;
  point.y = y;

  return point;
}

/// ------------------ FRACTAL FUNCTION ------------------

void fractal(FILE *stream, unsigned iter, unsigned iterMax, point_t center, double length){
  if ( iter < iterMax ){
    draw_square( stream, center, length, 255);

    int dir[] = { -1, 0, 1, 0, -1, 1, 1, -1, -1 };
    for ( unsigned i = 0 ; i < 8 ; i++){
      fractal(stream, iter + 1, iterMax, get_point(center.x + dir[i] * length, center.y + dir[i + 1] * length), length/3);
    }
  }
}

int main(){
  FILE *sierpinski_out = fopen("sierpinski.svg", "w");
  point_t center = get_point(0, 0);

  output_header(sierpinski_out);

  draw_square( sierpinski_out, center, LENGTH, 0);
  fractal(sierpinski_out, 0, ITER, center, LENGTH/3);

  output_footer(sierpinski_out);

  return 0;
}
