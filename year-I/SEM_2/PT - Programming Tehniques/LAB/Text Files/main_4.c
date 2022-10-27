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

int main(int argc, char *argv[]){ // ./main_4.x input1.txt output1.txt input2.txt output2.txt ... inputN.txt outputN.txt
  FILE *unix_file;
  FILE *dos_file;

  for (int i = 1 ; i < argc ; i += 2){
    unix_file = fopen(argv[i], "r");
    dos_file = fopen(argv[i+1], "w");

    if ( unix_file == NULL || dos_file == NULL ){
      break;
    }
    else {
      //printf("%s -> %s\n", argv[i], argv[i+1] );

      convert_UNIX_to_DOS(unix_file, dos_file);
    }

    fclose(unix_file);
    fclose(dos_file);
  }

  return 0;
}
