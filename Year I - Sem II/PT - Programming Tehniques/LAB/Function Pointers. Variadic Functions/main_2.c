#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

typedef struct point{
  float x;
  float y;
}point_t;

typedef struct object{
  unsigned type;
  double area;
  unsigned ID;
  union {
    struct {
      point_t pc;
      float r;
    }circle;
    struct {
      point_t p1;
      point_t p2;
      point_t p3;
    }triangle;
    struct {
      point_t p1;
      point_t p4;
    }rectangle;
  }shape;
  void (*get_object)(struct object *obj);
  void (*print_object)(struct object *obj);
  void (*calc_area)(struct object *obj);
}object_t;

/// ------------------ SHAPE GETTING FUNCTIONS ------------------

void get_circle(object_t *obj){
  obj->type = 0;

  printf(" * Getting Circle:\n");
  printf(" - radius: ");scanf("%f", &obj->shape.circle.r);
  printf(" - center: - x: ");scanf("%f", &obj->shape.circle.pc.x);
  printf("\t   - y: ");scanf("%f", &obj->shape.circle.pc.y);
}

void get_triangle(object_t *obj){
  obj->type = 1;

  printf(" * Getting Triangle:\n");
  printf(" - point 1: - x: ");scanf("%f", &obj->shape.triangle.p1.x);
  printf("\t    - y: ");scanf("%f", &obj->shape.triangle.p1.y);
  printf(" - point 2: - x: ");scanf("%f", &obj->shape.triangle.p2.x);
  printf("\t    - y: ");scanf("%f", &obj->shape.triangle.p2.y);
  printf(" - point 3: - x: ");scanf("%f", &obj->shape.triangle.p3.x);
  printf("\t    - y: ");scanf("%f", &obj->shape.triangle.p3.y);
}

void get_rectangle(object_t *obj){
  obj->type = 2;

  printf(" * Getting Rectangle:\n");
  printf(" - top-left point: - x: ");scanf("%f", &obj->shape.rectangle.p1.x);
  printf("\t\t   - y: ");scanf("%f", &obj->shape.rectangle.p1.y);
  printf(" - bottom-right point: - x: ");scanf("%f", &obj->shape.rectangle.p4.x);
  printf("\t\t       - y: ");scanf("%f", &obj->shape.rectangle.p4.y);
}

/// ------------------ SHAPE PRINTING FUNCTIONS ------------------

void print_circle(object_t *obj){
  printf(" * Circle %u:\n", obj->ID);
  printf(" - radius: %.2f\n", obj->shape.circle.r);
  printf(" - center: (%.2f, %.2f)\n\n", obj->shape.circle.pc.x, obj->shape.circle.pc.y);
}

void print_rectangle(object_t *obj){
  printf(" * Rectangle %u:\n", obj->ID);
  printf(" - top-left point: (%.2f, %.2f)\n", obj->shape.rectangle.p1.x, obj->shape.rectangle.p1.y);
  printf(" - bottom-right point: (%.2f, %.2f)\n\n", obj->shape.rectangle.p4.x, obj->shape.rectangle.p4.x);
}

void print_triangle(object_t *obj){
  printf(" * Triangle %u:\n", obj->ID);
  printf(" - point 1: (%.2f, %.2f)\n", obj->shape.triangle.p1.x, obj->shape.triangle.p1.y);
  printf(" - point 2: (%.2f, %.2f)\n", obj->shape.triangle.p2.x, obj->shape.triangle.p2.y);
  printf(" - point 2: (%.2f, %.2f)\n\n", obj->shape.triangle.p3.x, obj->shape.triangle.p3.y);
}

void print_area(object_t *obj){
  printf(" Area: %lf\n\n", obj->area);
}

/// ------------------ AREA CALCULATING FUNCTIONS ------------------

void calc_area_circle(object_t *obj){
  obj->area = obj->shape.circle.r * obj->shape.circle.r * PI;
}

void calc_area_triangle(object_t *obj){
  obj->area = (obj->shape.triangle.p1.x * (obj->shape.triangle.p2.y - obj->shape.triangle.p3.y) + obj->shape.triangle.p2.x * (obj->shape.triangle.p3.y - obj->shape.triangle.p1.y ) + obj->shape.triangle.p3.x * (obj->shape.triangle.p1.y - obj->shape.triangle.p2.y))/2;
}

void calc_area_rectangle(object_t *obj){
  obj->area =  abs(obj->shape.rectangle.p1.x - obj->shape.rectangle.p4.x) * abs(obj->shape.rectangle.p1.y - obj->shape.rectangle.p4.y);
}


void print_options(){
  printf("Choose Shape:\n");
  printf("  1. Circle\n");
  printf("  2. Triangle\n");
  printf("  3. Rectangle\n\n");
}

int main(){
  unsigned sizeObj = 0;
  object_t *arrObj;

  printf("Nr of Objects: "); scanf("%u", &sizeObj);
  arrObj = (object_t*)malloc(sizeObj * sizeof(object_t));

  for (unsigned i = 0 ; i < sizeObj ; i++){
    unsigned option;

    print_options();
    while (1) {
      printf(" - Option: "); scanf("%u", &option);
      switch ( option ){
        case 1:
          arrObj[i].get_object = &get_circle;
          arrObj[i].print_object = &print_circle;
          arrObj[i].calc_area = &calc_area_circle;
          break;
        case 2:
          arrObj[i].get_object = &get_triangle;
          arrObj[i].print_object = &print_triangle;
          arrObj[i].calc_area = &calc_area_triangle;
          break;
        case 3:
          arrObj[i].get_object = &get_rectangle;
          arrObj[i].print_object = &print_rectangle;
          arrObj[i].calc_area = &calc_area_rectangle;
          break;
      }
      if ( option == 1 || option == 2 || option == 3 ){
        arrObj[i].ID = i + 1;
        break;
      }
      else{
        printf("Invalid Option!\n");
      }
    }
  }

  for (unsigned i = 0 ; i < sizeObj ; i++){
    arrObj[i].get_object(&arrObj[i]);
    arrObj[i].calc_area(&arrObj[i]);
  }

  /// Printing Rectangles & Area
  printf("\n ~ RECTANGLES ~\n\n");
  for (unsigned i = 0 ; i < sizeObj ; i++){
    if ( arrObj[i].type == 2 ){
      arrObj[i].print_object(&arrObj[i]);
      print_area(&arrObj[i]);
    }
  }

  /// Printing Triangles & Area
  printf("\n ~ TRIANGLES ~\n\n");
  for (unsigned i = 0 ; i < sizeObj ; i++){
    if ( arrObj[i].type == 1 ){
      arrObj[i].print_object(&arrObj[i]);
      print_area(&arrObj[i]);
    }
  }

  /// Printing Circles & Area
  printf("\n ~ CIRCLES ~\n\n");
  for (unsigned i = 0 ; i < sizeObj ; i++){
    if ( arrObj[i].type == 0 ){
      arrObj[i].print_object(&arrObj[i]);
      print_area(&arrObj[i]);
    }
  }

  return 0;
}
