#include <stdio.h>
#include <stdlib.h>

typedef enum _shapeName {
  circle = 0,
  triangle = 1,
  rectangle = 2

}shapeName;

typedef struct _pair {
  float x;
  float y;
}pair;

typedef struct _object{
  shapeName flag:2;
  union {
    struct {
      pair O;
      float R;
    }circle;
    struct {
      pair A;
      pair B;
      pair C;
    }triangle;
    struct {
      pair A;
      pair B;
      pair C;
      pair D;
    }rectangle;
  }shape;
}object;


void printOption(){
  printf("Choose Shape:\n");
  printf("0 -> Circle\n");
  printf("1 -> Triangle:\n");
  printf("2 -> Rectangle:\n");
}

void createObject(object *myObject){
  switch ( myObject->flag ){
    case circle:
      printf("O - x: ");
      scanf("%f", &myObject->shape.circle.O.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.circle.O.y);

      printf("Radius: ");
      scanf("%f", &myObject->shape.circle.R);
      break;
    case triangle:
      printf("A - x: ");
      scanf("%f", &myObject->shape.triangle.A.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.triangle.A.y);

      printf("B - x: ");
      scanf("%f", &myObject->shape.triangle.B.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.triangle.B.y);

      printf("C - x: ");
      scanf("%f", &myObject->shape.triangle.C.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.triangle.C.y);
      break;
    case rectangle:
      printf("A - x: ");
      scanf("%f", &myObject->shape.rectangle.A.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.rectangle.A.y);

      printf("B - x: ");
      scanf("%f", &myObject->shape.rectangle.B.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.rectangle.B.y);

      printf("C - x: ");
      scanf("%f", &myObject->shape.rectangle.C.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.rectangle.C.y);

      printf("D - x: ");
      scanf("%f", &myObject->shape.rectangle.D.x);
      printf("  - y: ");
      scanf("%f", &myObject->shape.rectangle.D.y);
      break;
  }
}

void printObject(object myObject){
  printf("\n");
  switch ( myObject.flag ){
    case circle:
      printf("O(%.2f, %.2f)\n", myObject.shape.circle.O.x, myObject.shape.circle.O.y);
      printf("R =  %.2f\n", myObject.shape.circle.R);
      break;
    case triangle:
      printf("A(%.2f, %.2f)\n", myObject.shape.triangle.A.x, myObject.shape.triangle.A.y);
      printf("B(%.2f, %.2f)\n", myObject.shape.triangle.B.x, myObject.shape.triangle.B.y);
      printf("C(%.2f, %.2f)\n", myObject.shape.triangle.C.x, myObject.shape.triangle.C.y);
      break;
    case rectangle:
      printf("A(%.2f, %.2f)\n", myObject.shape.rectangle.A.x, myObject.shape.rectangle.A.y);
      printf("B(%.2f, %.2f)\n", myObject.shape.rectangle.B.x, myObject.shape.rectangle.B.y);
      printf("C(%.2f, %.2f)\n", myObject.shape.rectangle.C.x, myObject.shape.rectangle.C.y);
      printf("D(%.2f, %.2f)\n", myObject.shape.rectangle.C.x, myObject.shape.rectangle.C.y);
      break;
  }
  printf("\n");
}

int main(){
  unsigned option;

  unsigned nrObjects;
  object *myObject = malloc(sizeof(object));

  printf("How many shapes do you want? ");
  scanf("%u", &nrObjects);
  myObject = realloc(myObject, nrObjects*sizeof(object));

  printOption();

  for (int i = 0 ; i < nrObjects ; i++ ){
    printf("\nShape:");
    scanf("%u", &option);

    if ( 0 <= option && option <=2 ){
      myObject[i].flag = option;
    }
    else {
      printf("wrong option");
      i--;
      continue;
    }

    createObject( &myObject[i] );
  }

  for (int i = 0 ; i < nrObjects ; i++ ){
    printObject( myObject[i] );
  }

  return 0;
}
