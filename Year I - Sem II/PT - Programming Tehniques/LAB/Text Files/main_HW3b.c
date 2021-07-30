#include <stdio.h>
#include <stdlib.h>

#define SIZE 500 // base: 1000

void print_header(FILE* stream_out){
  fprintf(stream_out, "P3\n");
  fprintf(stream_out, "%u %u\n", SIZE, SIZE);
  fprintf(stream_out, "255\n");
  //fprintf(stream_out, "%u\n", SIZE-1);
}

void make_gradient(FILE* stream_out, float *R, float *G, float *B, float *color){
  for (unsigned i = 0; i < SIZE ; i++){
    (*color) = 0;
    for (unsigned j = 0; j < SIZE ; j++){
      //fprintf(stream_out, "%u %u %u ", j, j, j);
      fprintf(stream_out, "%u %u %u ", (unsigned)(*R), (unsigned)(*G), (unsigned)(*B));
      (*color) += (float)255/(SIZE+1);
    }
    fprintf(stream_out, "\n");
  }
}

int main(){
  FILE* pic_out = fopen("pic_3b.ppm", "w");
  float *color = (float*)malloc(sizeof(float));
  float green = 0;

  print_header(pic_out);

  make_gradient(pic_out, color, &green, color, color);

  fclose(pic_out);

  return 0;
}
