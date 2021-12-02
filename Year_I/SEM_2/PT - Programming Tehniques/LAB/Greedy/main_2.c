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

/// -------------- PATH FINDING FUNCTIONS --------------

unsigned find_greedy_path(unsigned cityNr, unsigned totalDist, unsigned visited[], unsigned nrVisited){
  unsigned nextCity = cityNr;
  unsigned minDist = UINT_MAX;

  visited[cityNr] = nrVisited;

  /// minimum distance & next city finder
  for (unsigned crtCity = 0 ; crtCity < SIZE ; crtCity++){
    if ( dists[cityNr][crtCity] == 0 || visited[crtCity]){ // visited/same city skipped
      continue;
    }
    if ( dists[cityNr][crtCity] < minDist ){
      minDist = dists[cityNr][crtCity];
      nextCity = crtCity;
    }
  }

  if ( nextCity == cityNr ){ // no next city found (dead end / path end)
    if ( nrVisited == SIZE ){
      return totalDist;
    }
    else {
      return 0;
    }
  }
  else{ // path continues
    return find_greedy_path(nextCity, totalDist + minDist, visited, nrVisited + 1);
  }
}

int main(){
  FILE *cities_in = fopen("cities.txt", "r");
  unsigned visitedGreedy[SIZE] = {0}, visitedAll[SIZE] = {0};

  get_cities(cities_in);
  print_cities();

  printf("Greedy Method:\n");
  unsigned dist = find_greedy_path(1, 0, visitedGreedy, 1);
  if ( dist == 0 ){
    printf("No greedy solution (doesn't reach all cities)!\n");
  }
  else {
    printf(" - Distance: %u km ",dist);
    print_path(visitedGreedy, SIZE);
  }

  return 0;
}
