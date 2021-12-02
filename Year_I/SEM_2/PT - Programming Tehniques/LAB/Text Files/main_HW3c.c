#include <stdio.h>
#include <stdlib.h>

#define SIZE 500 // base: 1000

void print_header(FILE* stream_out){
  fprintf(stream_out, "P3\n");
  fprintf(stream_out, "%u %u\n", SIZE, SIZE);
  fprintf(stream_out, "255\n");
}

void get_header(FILE* stream_in, unsigned *cols, unsigned *rows){
  fscanf(stream_in, "P3\n");
  fscanf(stream_in, "%u %u\n", cols, rows);
  fscanf(stream_in, "255\n");
}

void insert_text_gradient(FILE* stream_out, char* text){
  float color;
  unsigned g = 0;

  unsigned textEnd = 0;
  unsigned bit;

  print_header(stream_out);

  for (unsigned i = 0; i < SIZE ; i++){
    color = 0;
    for (unsigned j = 0; j < SIZE ; j++){
      if ( !textEnd ){
        if ( text[((i*SIZE)+j)/8] == '\0' ){
          textEnd = 1;
          bit = 0;
        }
        bit = (text[((i*SIZE)+j)/8] >> (7-((i*SIZE)+j)%8)) & 0x1;
      }
      fprintf(stream_out, "%u %u %u ", (unsigned)color, ((g<<1)>>1)+bit, (unsigned)color);

      color += (float)255/(SIZE+1);
    }
    fprintf(stream_out, "\n");
  }
}

void extract_text(FILE *stream_in){
  unsigned rows = 0, cols = 0;
  unsigned pixel = 0;
  unsigned r, g, b;

  char* text = (char*)malloc(2*sizeof(char));
  unsigned bit;

  get_header(stream_in, &cols, &rows);

  while ( fscanf(stream_in, "%u %u %u", &r, &g, &b) == 3 ){
    if ( pixel % 8 == 0 && pixel != 0 ){
      if ( text[pixel/8-1] == 0 ){
        break;
      }
      text = (char*)realloc(text,(pixel/8 + 2)*sizeof(char));
    }
    bit = g & 0x1;
    text[pixel/8] = (text[pixel/8] << 1) + bit;

    pixel++;
  }
  text[pixel/8] = '\0';

  printf("%*s", pixel/8-1, text);
}

int main(int argc, char *argv[]){
  char* message = "Hello world!";

  /// INSERTION
  FILE* gradient_out = fopen("pic_3c.ppm", "w");

  insert_text_gradient(gradient_out, message);

  fclose(gradient_out);

  /// EXTRACTION
  if ( argc != 2 ){
    fprintf(stderr, "Wrong number of arguments!\n");
    exit(EXIT_FAILURE);
  }

  FILE* pic_in = fopen(argv[1], "r");

  if ( pic_in == NULL ){
    fprintf(stderr, "File open error!\n");
    exit(EXIT_FAILURE);
  }

  extract_text(pic_in);

  fclose(pic_in);

  return 0;
}
