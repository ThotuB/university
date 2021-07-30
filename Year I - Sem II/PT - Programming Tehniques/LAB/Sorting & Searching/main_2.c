#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSING_GRADE 4.50
#define SCHOLARSHIP_GRADE 8.50

typedef struct student {
  char name[50];
  float grade;
} student_t;

/// ---------- BASIC FUNCTIONS --------------
void printOptions(){
  printf("0. Exit program\n");
  printf("1. Give N, number of students\n");
  printf("2. Enter the students\n");
  printf("3. Display class\n");
  printf("4. Display class ordered alphabetically\n");
  printf("5. Display class ordered by grade\n");
  printf("6. Display failed students\n");
  printf("7. Display students with scholarship\n");
}

void setOrd(student_t **Arr, student_t *studArr, int size){
  for (int i=0; i<size ; i++){
    Arr[i]=&studArr[i];
  }
}

/// ---------- PRINT FUNCTIONS --------------
void printStudent(student_t stud){
  for ( int i=0 ; stud.name[i] != '\0'; i++){
    printf("%c", stud.name[i]);
  }
  printf(" - %1.2f",stud.grade);
  printf("\n");
}

void printArrStuds(student_t *Arr, int size){
  for (int i=0; i < size ; i++){
    printStudent(Arr[i]);
  }
}

void printArrPtrs(student_t **Arr, int size){
  for (int i=0; i < size ; i++){
    printStudent(*Arr[i]);
  }
}

void printFailed(student_t **Arr,int size, float passGrade){
  for (int i=size-1; i >= 0 ; i--){
    if ( (*Arr[i]).grade < passGrade ){
      printStudent( *Arr[i] );
    }
    else{
      break;
    }
  }
}

void printSchShp(student_t **Arr,int size, float schShpGrade){
  for (int i=0; i < size ; i++){
    if ( (*Arr[i]).grade >= schShpGrade ){
      printStudent( *Arr[i] );
    }
    else {
      break;
    }
  }
}

/// ---------- SORTING FUNCTIONS --------------
void sortAlpha(student_t **alphaOrd, int size){
  for (int i = 0; i < size - 1 ; i++){
    for (int j = i + 1 ; j < size ; j++){
      if ( strcmp( (*alphaOrd[i]).name, (*alphaOrd[j]).name ) > 0 ){
        student_t *auxStud=alphaOrd[i];
        alphaOrd[i]=alphaOrd[j];
        alphaOrd[j]=auxStud;
      }
    }
  }
}

void sortGrade(student_t **gradeOrd, int size){
  for (int i = 0; i < size - 1 ; i++){
    for (int j = i + 1 ; j < size ; j++){
      if ( (*gradeOrd[i]).grade < (*gradeOrd[j]).grade ){
        student_t *auxStud=gradeOrd[i];
        gradeOrd[i]=gradeOrd[j];
        gradeOrd[j]=auxStud;
      }
    }
  }
}

/// -*-*-*-*-*-*-*- MAIN FUNCTION -*-*-*-*-*-*-*-

int main(){
  int option;
  int noStudents=0;

  student_t *studArr=malloc(0);
  student_t **alphaOrd=malloc(0);
  int alphaCheck=0;
  student_t **gradeOrd=malloc(0);
  int gradeCheck=0;

  printOptions();
  while ( 1 ){
    printf("\nChoose Option: ");
    scanf("%d",&option);
    switch ( option ) {
      case 0:     // EXITS APP
        return 0;
        break;

      case 1:     // READS NUMBER OF STUDENTS
        printf("No of Students: ");
        scanf("%d", &noStudents);
        studArr=realloc(studArr, noStudents*sizeof(student_t));
        break;

      case 2:     // READS STUDENT DETAILS
        for (int i=0; i < noStudents ; i++){
          printf("Student: ");
          scanf("%50s", studArr[i].name);
          printf("Grade: ");
          scanf("%f", &studArr[i].grade);
        }
        break;

      case 3:     // PRINTS ALL STUDENTS
        printArrStuds(studArr,noStudents);
        break;

      case 4:     // PRINTS ALL STUDENTS ORDERED ALPHABETICALLY
        if (!alphaCheck){
          alphaOrd=realloc(alphaOrd, noStudents*sizeof(student_t*));
          setOrd(alphaOrd,studArr,noStudents);
          sortAlpha(alphaOrd,noStudents);
          alphaCheck=1;
        }
        printArrPtrs(alphaOrd,noStudents);
        break;

      case 5:     // PRINTS ALL STUDENTS ORDERED BY GRADE
        if (!gradeCheck){
          gradeOrd=realloc(gradeOrd, noStudents*sizeof(student_t*));
          setOrd(gradeOrd,studArr,noStudents);
          sortGrade(gradeOrd,noStudents);
          gradeCheck=1;
        }
        printArrPtrs(gradeOrd,noStudents);
        break;

      case 6:     // PRINTS ALL FAILED STUDENTS
        if (!gradeCheck){
          gradeOrd=realloc(gradeOrd, noStudents*sizeof(student_t*));
          setOrd(gradeOrd,studArr,noStudents);
          sortGrade(gradeOrd,noStudents);
          gradeCheck=1;
        }
        printFailed(gradeOrd, noStudents, PASSING_GRADE);
      break;

      case 7:     // PRINTS ALL STUDENTS WITH SCHOLARSHIP
        if (!gradeCheck){
          gradeOrd=realloc(gradeOrd, noStudents*sizeof(student_t*));
          setOrd(gradeOrd,studArr,noStudents);
          sortGrade(gradeOrd,noStudents);
          gradeCheck=1;
        }
        printSchShp(gradeOrd, noStudents, SCHOLARSHIP_GRADE);
      break;
      default:
        return 0;
    }
  }
  return 0;
}
