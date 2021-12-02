#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
    unsigned code;
    char title[200];
}entry_t;

void print_entry(entry_t *Arr, unsigned index){
  printf("Code: %u\n", Arr[index].code);
  printf("Title: %s\n\n", Arr[index].title);
}

void get_entries(entry_t *Arr, FILE *stream_in, unsigned *size){
  int pass;
  (*size) = 0;

  while ( !feof(stream_in) ){
    pass = fscanf(stream_in, "%d ", &Arr[*size].code);
    if ( !pass ){
      break;
    }
    fgets(Arr[*size].title, 200, stream_in);
    Arr[*size].title[strlen(Arr[*size].title) - 1] = '\0';

    (*size)++;
  }
  (*size)--;
}

int interpolation_search(entry_t *Arr, unsigned size, unsigned code){
  long long unsigned mid, left, right;
  left = 0; right = size - 1;

  if ( Arr[left].code >= code ){
    return -1;
  }

  do{
    mid = left + (right - left) * (code - Arr[left].code) / (Arr[right].code - Arr[left].code);
    //printf("%llu - %llu - %llu\n", left, mid, right);
    if ( code > Arr[mid].code ){
      left = mid + 1;
    }
    else {
      right = mid - 1;
    }
  }while ( (left <= right) && (Arr[mid].code != code) && (Arr[left].code != Arr[right].code) && (Arr[left].code <= code) && (code <= Arr[right].code) );

  if ( code == Arr[mid].code ){
    return mid;
  }
  return -1;
}

void linear_search(entry_t *Arr, unsigned size, char* title){
  unsigned titleLen = strlen(title);

  for (unsigned i = 0; i < size ; i++){
    if ( strncasecmp(title, Arr[i].title, titleLen) == 0 ){
      printf("%s\n", Arr[i].title);
    }
  }
}

unsigned get_code(){
  unsigned newCode;

  printf("Code to Search: ");
  scanf("%u", &newCode);
  getchar();

  return newCode;
}

char* get_title(){
  char *newTitle = (char*)malloc(200*sizeof(char));

  printf("Title to Search: ");
  scanf("%200s", newTitle);

  //printf("%d %s", strlen(newTitle), newTitle);
  return newTitle;
}

int main() {
  entry_t *entries = (entry_t*)malloc(5000 * sizeof(entry_t));
  unsigned size;

  FILE *file_in = fopen("FisierCORcrescator.txt", "r");

  if ( !file_in ){
    perror("Error: ");
    exit(1);
  }

  get_entries(entries, file_in, &size);

  if ( size == 0 ){
    printf("No entries found!\n");
    exit(1);
  }

  /// Interpolation Search - Code
  unsigned code = get_code();
  int index = interpolation_search(entries, size, code);
  if ( index == -1 ){
    printf("No entry found with code: %d\n\n", code);
  }
  else {
    print_entry(entries, index);
  }

  /// Linear Search - Title
  char* title = get_title();
  linear_search(entries, size, title);

  free(entries);

  return 0;
}
