#include <stdio.h>

#define ASCII_CHARS 128

unsigned freq[ASCII_CHARS] = {0};
const char *weird_chars[] = {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE"};

void print_freq(FILE *stream_out){
  fprintf(stream_out, "Dec\tHex\tChar\t\tAppearance\n");
  for (unsigned i = 0 ; i < ASCII_CHARS ; i++){
    if ( freq[i] != 0 ){
      fprintf(stream_out, "%u\t%x\t", i, i );
      if ( i < 33 ){
        fprintf(stream_out, "%s\t", weird_chars[i]);
      }
      else if ( i == 127 ){
        fprintf(stream_out, "DEL");
      }
      else {
        fprintf(stream_out, "%c\t", (char)i);
      }
      fprintf(stream_out, "\t \t%u\n", freq[i]);
    }
  }
}

void get_freq(FILE *stream_in){
  char c;

  while ( fscanf(stream_in, "%c", &c) == 1 ){
    if ( (unsigned)c < ASCII_CHARS){
      freq[(unsigned)c]++;
    }
  }
}

int main(){
  FILE *stream_in;
  //stream_in = stdin;
  stream_in = fopen("main_2.c", "r");
  FILE *stream_out = stdout;

  get_freq(stream_in);
  print_freq(stream_out);

  fclose(stream_in);
  fclose(stream_out);

  return 0;
}
