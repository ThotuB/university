#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE 5 // base size: 5 (Tab. 3)

unsigned dists[SIZE][SIZE];
char *cities[] = {"Timisoara", "Oradea", "Cluj-Napoca", "Iasi", "Bucuresti", "Constanta", "Brasov", "Galati"}; // more cities for larger SIZE

unsigned minDist = UINT_MAX;
unsigned minPath[SIZE];

/// -------------- INITIALIZING FUNCTION --------------

void get_cities(FILE *stream){
  for (unsigned i = 0 ; i < SIZE ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      fscanf(stream, "%u", &dists[i][j]);
    }
  }
}

/// -------------- PRINTING FUNCTIONS --------------

void print_cities(){
  printf("\t\t");
  for (unsigned i = 0 ; i < SIZE ; i++){
    printf("%-s\t", cities[i]);
    if ( strlen(cities[i]) < 8 ){
      printf("\t");
    }
  }
  for (unsigned i = 0 ; i < SIZE ; i++){
    printf("\n%13s ", cities[i]);
    for (unsigned j = 0 ; j < SIZE ; j++){
      printf("\t%u\t ", dists[i][j]);
    }
  }
  printf("\n\n");
}

void print_path(unsigned path[], unsigned size){
  printf("( ");
  for (unsigned i = 0 ; i < size ; i++){
      printf("%s ", cities[path[i]]);
      if ( i < size - 1 ){
        printf("-> ");
      }
  }
  printf(")\n");
}

void copy_array(unsigned dest[], unsigned src[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    dest[i] = src[i];
  }
}

/// -------------- PATH FINDING FUNCTIONS --------------

void find_backtracking_path(unsigned cityNr, unsigned totalDist, unsigned visited[], unsigned nrVisited){
  static unsigned path[SIZE];

  visited[cityNr] = 1;
  path[nrVisited-1] = cityNr;

  if ( nrVisited == SIZE ){
    if ( totalDist < minDist ){
      minDist = totalDist;
      copy_array(minPath, path, SIZE);
    }
  }
  else {
    unsigned nextCity = cityNr;

    for (unsigned crtCity = 0 ; crtCity < SIZE ; crtCity++){
      //printf("%s -> ", cities[cityNr]);printf("%s - ", cities[crtCity]);
      if ( dists[cityNr][crtCity] == 0 || visited[crtCity] ){ // no distance/visited/skipped cities -> continue
        //printf("skip\n");
        continue;
      }
      nextCity = crtCity;
      //printf("valid\n");
      find_backtracking_path(nextCity, totalDist + dists[cityNr][nextCity], visited, nrVisited + 1);
      visited[nextCity] = 0;
    }
  }
}

int main(){
  FILE *cities_in = fopen("cities.txt", "r");
  unsigned visitedGreedy[SIZE] = {0};

  get_cities(cities_in);
  print_cities();

  printf("Backtracking Method:\n");
  find_backtracking_path(0, 0, visitedGreedy, 1);

  printf(" - Distance: %u km ", minDist);
  print_path(minPath, SIZE);

  return 0;
}
