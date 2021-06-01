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

void copy_array(unsigned dest[], unsigned src[], unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    dest[i] = src[i];
  }
}

/// -------------- PATH FINDING FUNCTIONS --------------

void find_all_paths(unsigned cityNr, unsigned totalDist, unsigned visited[], unsigned nrVisited){
  unsigned nextCity = cityNr;

  visited[cityNr] = nrVisited;

  for (unsigned crtCity = 0 ; crtCity < SIZE ; crtCity++){
    if ( dists[cityNr][crtCity] == 0 || visited[crtCity]){ // visited/same city skipped
      continue;
    }
    nextCity = crtCity;
    find_all_paths(nextCity, totalDist + dists[cityNr][nextCity], visited, nrVisited + 1); // path continues
    visited[nextCity] = 0;
  }

  if ( nextCity == cityNr && nrVisited == SIZE){ // no next city found (dead end / path end)
    printf(" - Distance: %u km ", totalDist);
    print_path(visited, SIZE);
  }
}

int main(){
  FILE *cities_in = fopen("cities.txt", "r");
  unsigned visitedGreedy[SIZE] = {0}, visitedAll[SIZE] = {0};

  get_cities(cities_in);
  print_cities();

  printf("\nAll Paths:\n");
  find_all_paths(0, 0, visitedAll, 1);

  printf("\n * Greedy does not find the optimal solution for Tab. 3 *\n");
  return 0;
}
