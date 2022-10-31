#include <stdio.h>
#include <stdlib.h>

typedef enum _starType {
  main_sequence = 1,
  binary = 2,
  variable_light = 3
}starType;

typedef struct star {
  char *name;
  starType flag:2;
  union {
    struct{
      int age:2;
      char color[12];
    }mainSequence;
    struct{
      double radius1;
      double radius2;
    }binary;
    struct{
      unsigned lumLow;
      unsigned lumHigh;
      double lightPeriod;
    }variableLight;
  }type;
}star_t;

void printOption(){
  printf("Choose Star Type:\n");
  printf("1 -> Main Sequence Star\n");
  printf("2 -> Binary Star:\n");
  printf("3 -> Variable Light:\n");
}

void createStar(star_t *myStar){
  char g = getchar();
  printf("* Star Name: ");
  myStar->name = malloc(sizeof(char));
  int i = 0;
  for ( char c = getchar(); c != '\n' ; c = getchar() ){
    myStar->name = realloc(myStar->name, (i + 1)*sizeof(char));
    myStar->name[i] = c;
    i++;
  }
  myStar->name[i] = '\0';

  if ( myStar->flag == main_sequence ){
    unsigned age;

    printf("- Age Group: ");
    scanf("%u", &age);
    myStar->type.mainSequence.age = age - 1;
    printf("- Color: ");
    scanf("%11s", myStar->type.mainSequence.color);
  }
  else if ( myStar->flag == binary ){
    printf("- Rotation Radius (Star I): ");
    scanf("%lf", &myStar->type.binary.radius1);
    printf("- Rotation Radius (Star II): ");
    scanf("%lf", &myStar->type.binary.radius2);
  }
  else if ( myStar->flag == variable_light ){
    printf("- Lowest Luminocity: ");
    scanf("%u", &myStar->type.variableLight.lumLow);
    printf("- Highest Luminocity: ");
    scanf("%u", &myStar->type.variableLight.lumHigh);
    printf("- Light Periodicity (Earth Days): ");
    scanf("%lf", &myStar->type.variableLight.lightPeriod);
  }
}

void printStar(star_t myStar){
  printf("\n");
  for (int i = 0; myStar.name[i] != '\0'; i++){
      printf("%c", myStar.name[i]);
  }

  switch ( myStar.flag ){
    case main_sequence:
      printf(" - Main Sequence Star:");
      printf("\n* Age Group: %u", myStar.type.mainSequence.age + 1);
      printf("\n* Color: %-12s", myStar.type.mainSequence.color);
      break;

    case binary:
      printf(" - Binary Star:");
      printf("\n* Rotation Radius (Star I): %lf", myStar.type.binary.radius1);
      printf("\n* Rotation Radius (Star II): %lf", myStar.type.binary.radius2);
      break;

    case variable_light:
      printf(" - Variable Light Star:");
      printf("\n* Luminocity: %u - %u", myStar.type.variableLight.lumLow, myStar.type.variableLight.lumHigh);
      printf("\n* Light Periodicity (Earth Days): %lf", myStar.type.variableLight.lightPeriod);
      break;
  }
  printf("\n");
}

int main(){
  unsigned option;

  star_t myStar;

  printOption();

  printf("\nStar Type:");
  scanf("%u[^\n]%*[^\n]", &option);

  if ( 1 <= option && option <= 3 ){
    myStar.flag = option;
  }
  else {
    printf("wrong option");
    return 0;
  }

  createStar( &myStar );
  printStar( myStar );

  return 0;
}
