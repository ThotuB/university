#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE 5 // base size: 5 (Tab. 3)

typedef struct _dist {
  unsigned fromCity;

  unsigned distance;

  unsigned toCity;
}dist_t;

dist_t dists[SIZE][SIZE];
char *cities[] = {"Timisoara", "Oradea", "Cluj-Napoca", "Iasi", "Bucuresti", "Constanta", "Brasov", "Galati"}; // more cities for larger SIZE
char *path[SIZE];

/// -------------- INITIALIZING FUNCTION --------------

void get_cities(FILE *stream){
  for (unsigned i = 0 ; i < SIZE ; i++){
    for (unsigned j = 0 ; j < SIZE ; j++){
      dists[i][j].fromCity = i;
      fscanf(stream, "%u", &dists[i][j].distance);
      dists[i][j].toCity = j;
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
      printf("\t%u\t ", dists[i][j].distance);
    }
  }
  printf("\n\n");
}

void print_ordered_cities(){
  for (unsigned i = 0 ; i < SIZE ; i++){
    // city printing
    printf("\t\t");
    for (unsigned j = 0 ; j < SIZE ; j++){
      printf("%-s\t", cities[dists[i][j].toCity] );
      if ( strlen(cities[dists[i][j].toCity]) < 8 ){
        printf("\t");
      }
    }

    // distance printing
    printf("\n%13s ", cities[dists[i][0].fromCity]);
    for (unsigned j = 0 ; j < SIZE ; j++){
      printf("\t%u\t ", dists[i][j].distance);
    }
    printf("\n\n");
  }
}

void print_path(unsigned size){
  printf("( ");
  for (unsigned i = 0 ; i < size ; i++){
    printf("%s --> ", path[i]);
  }
  printf("%s )\n", path[0]);
}

/// -------------- CITIES FUNCTIONS --------------

int compare_dists(const void *a, const void *b){
  dist_t *dist1 = (dist_t*)a;
  dist_t *dist2 = (dist_t*)b;

  return (dist1->distance - dist2->distance);
}

void order_dists(){
  for (unsigned i = 0 ; i < SIZE ; i++){
    qsort(dists[i], SIZE, sizeof(dist_t), compare_dists);
  }
}

unsigned valid_last_city( unsigned cityNr){
  char *firstCity = path[0];

  for (unsigned j = 0 ; j < SIZE ; j++){
    if ( cities[dists[cityNr][j].toCity]  == firstCity ){
      return dists[cityNr][j].distance;
    }
  }
}

/// -------------- PATH FINDING FUNCTIONS --------------

void find_greedy_path(unsigned cityNr, unsigned distTotal, unsigned visited[], unsigned nrVisited){
  visited[cityNr] = 1;
  path[nrVisited - 1] = cities[cityNr];

  if ( nrVisited == SIZE && valid_last_city(cityNr)){ // end of path
    printf(" - Distance: %u km ", distTotal + valid_last_city(cityNr));
    print_path(nrVisited);
    exit(0);
  }
  else {
    unsigned nextCity;

    for (unsigned i = 1 ; i < SIZE ; i++){
      unsigned crtCity = dists[cityNr][i].toCity;
      unsigned crtDist = dists[cityNr][i].distance;

      if ( crtDist == 0 || visited[crtCity] ){ // no distance/visited/skipped cities -> continue
        continue;
      }
      nextCity = crtCity;

      if ( nextCity != cityNr ){ // next city found
        find_greedy_path(nextCity, distTotal + crtDist, visited, nrVisited + 1);
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
  order_dists();
  print_ordered_cities();

  printf("Greedy Method:\n");
  find_greedy_path(0, 0, visitedGreedy, 1);

  return 0;
}
