#include <stdio.h>

void convert_UNIX_to_DOS(FILE *stream_in, FILE *stream_out){
  char c;

  while ( fscanf(stream_in, "%c", &c) == 1 ){
    if ( c == '\n' ){
      fprintf(stream_out, "\r");
    }
    fprintf(stream_out, "%c", c);
  }
}

int main(){
  FILE *unix_file = fopen("unix_in.txt", "r");
  FILE *dos_file = fopen("dos_out.txt", "w");

  convert_UNIX_to_DOS(unix_file, dos_file);

  fclose(unix_file);
  fclose(dos_file);

  return 0;
}
