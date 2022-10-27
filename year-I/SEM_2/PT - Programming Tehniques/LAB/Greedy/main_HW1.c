#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE 5 // base size: 5 (Tab. 3)

unsigned dists[SIZE][SIZE];
char *cities[] = {"Timisoara", "Oradea", "Cluj-Napoca", "Iasi", "Bucuresti", "Constanta", "Brasov", "Galati"}; // more cities for larger SIZE

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

void print_path(unsigned visited[], unsigned size){
  printf("( ");
  for (unsigned i = 1 ; i <= size ; i++){
    for (unsigned j = 0 ; j < size ; j++){
      if ( visited[j] == i ){
        printf("%s ", cities[j]);
        if ( i < size ){
          printf("-> ");
        }
        break;
      }
    }
  }
  printf(")\n");
}

unsigned valid_last_city( unsigned cityNr, unsigned visited[]){
  unsigned firstCity = 0;

  for (unsigned i = 0 ; i < SIZE ; i++){
    if ( visited[i] == 1 ){
      firstCity = i;
      break;
    }
  }

  return dists[cityNr][firstCity];
}

/// -------------- PATH FINDING FUNCTIONS --------------

void find_greedy_path(unsigned cityNr, unsigned totalDist, unsigned visited[], unsigned nrVisited){
  visited[cityNr] = nrVisited;

  if ( nrVisited == SIZE && valid_last_city(cityNr, visited)){ //
    printf(" - Distance: %u km ", totalDist + valid_last_city(cityNr, visited));
    print_path(visited, SIZE);
    exit(0);
  }
  else{
    unsigned skipped[SIZE] = {0};
    unsigned nextCity;
    unsigned minDist;

    /// minimum distance & next city finder
    for (unsigned i = 0 ; i < SIZE - nrVisited ; i++){
      minDist = UINT_MAX;
      nextCity = cityNr;

      for (unsigned crtCity = 0 ; crtCity < SIZE ; crtCity++){
        if ( dists[cityNr][crtCity] == 0 || visited[crtCity] || skipped[crtCity] ){ // no distance/visited/skipped cities -> continue
          continue;
        }
        if ( dists[cityNr][crtCity] < minDist ){
          minDist = dists[cityNr][crtCity];
          nextCity = crtCity;
        }
      }
      skipped[nextCity] = 1;

      if ( nextCity != cityNr ){ // next city was found
        find_greedy_path(nextCity, totalDist + dists[cityNr][nextCity], visited, nrVisited + 1);
        visited[nextCity] = 0;
      }
    }
  }
}

int main(){
  FILE *cities_in = fopen("citiesHW.txt", "r");
  unsigned visitedGreedy[SIZE] = {0};

  get_cities(cities_in);
  print_cities();

  printf("Greedy Method:\n");
  find_greedy_path(0, 0, visitedGreedy, 1);

  return 0;
}
