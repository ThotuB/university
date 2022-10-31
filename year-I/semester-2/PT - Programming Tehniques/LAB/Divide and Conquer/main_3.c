#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITER 8  // no of iterations
#define ORDER 3 // order means something else in my case ( n-th order polynomial ) - don't go over 5 with many iterations

#define CENTER_X 1280
#define CENTER_Y 620

#define LENGTH 500

double PI = acos(-1);

typedef struct _point{
  double x;
  double y;
}point_t;

typedef struct _poly{
  point_t point[ORDER];
}poly_t;

/// ------------------ HEADER & FOOTER OUTPUT ------------------

void output_header(FILE *stream){
  fprintf(stream, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" overflow=\"scroll\">\n");
}

void output_footer(FILE *stream){
  fprintf(stream, "</svg>");
}

/// ------------------ DRAWING FUNCTIONS ------------------

void draw_line(FILE *stream, point_t A, point_t B, unsigned color){
  double Ax = CENTER_X + A.x;
  double Ay = CENTER_Y - A.y;

  double Bx = CENTER_X + B.x;
  double By = CENTER_Y - B.y;

  fprintf(stream, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"rgb(%u,%u,%u)\" stroke-width=\"1\" />\n", Ax, Ay, Bx, By, color, color, color);
}

void draw_circle(FILE *stream, point_t C, double length){
  fprintf(stream, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" stroke-width=\"1\" />\n", CENTER_X + C.x, CENTER_Y - C.y, length );
}

void draw_poly(FILE *stream, unsigned order, poly_t poly, unsigned iter){
  unsigned color;

  for (unsigned i = 0 ; i < order ; i++){
    if (iter != 0 ){
      if ( i == 1 ){
        color = 255;
      }
      else {
        color = 0;
      }
    }
    draw_line(stream, poly.point[i % order], poly.point[(i + 1) % order], color);
  }
}

/// ------------------ CALCULATING FUNCTIONS ------------------

double calc_circumscribed_circle_radius(unsigned order, double length){ // distance: center - vertex
  double radius = length / (2 * sin(PI / order));

  return radius;
}

double calc_inscribed_circle_radius(unsigned order, double length){ // distance: center - edge
  double radius = length / (2 * tan(PI / order));

  return radius;
}

double calc_exterior_angle(unsigned order){ // angle: vertex - vertex - vertex
  double angle = ((order - 2) * PI)/order;

  return angle;
}

double calc_interior_angle(unsigned order){ // angle: vertex - center - vertex
  double angle = 2 * PI / order;

  return angle;
}

/// ------------------ GETTING FUNCTIONS ------------------

point_t get_point(double x, double y){
  point_t point;

  point.x = x;
  point.y = y;

  return point;
}

poly_t get_poly(unsigned order, point_t center, double length, double phase){ // gets all vertices of polygon given: order, center, side length, initial phase/orientation
  poly_t polygon;
  double angle = 2 * PI / order;
  double dist = calc_circumscribed_circle_radius(order, length);

  for (unsigned i = 0 ; i < order ; i++){
    polygon.point[i].x = center.x + cos(i * angle + phase) * dist;
    polygon.point[i].y = center.y + sin(i * angle + phase) * dist;
  }

  return polygon;
}

/// ------------------ FRACTAL FUNCTION ------------------

void fractal(FILE *stream, unsigned iter, unsigned iterMax, unsigned order, point_t center, double length, double orient){
  if ( iter < iterMax ){
    poly_t poly = get_poly(order, center, length, orient);

    draw_poly(stream, order, poly, iter);

    double dist = calc_inscribed_circle_radius(order, length) + calc_inscribed_circle_radius(order, length/3);

    double interAngle = calc_interior_angle(order);
    double exterAngle = calc_exterior_angle(order);
    double phase = interAngle/2;

    for (unsigned i = 2 ; i < order + 2 && !( iter > 0 && i == order + 1) ; i++){
      point_t newCenter;
      double angle = orient + i * interAngle + phase;

      newCenter.x = center.x + cos(angle) * dist;
      newCenter.y = center.y + sin(angle) * dist;

      fractal(stream, iter + 1, iterMax, order, newCenter, length/3, angle - phase + exterAngle);
    }
  }
}

int main(){
  FILE *koch_out = fopen("koch.svg", "w");

  output_header(koch_out);

  fractal(koch_out, 0, ITER, ORDER, get_point(0, 0), LENGTH, 0);

  output_footer(koch_out);

  return 0;
}
