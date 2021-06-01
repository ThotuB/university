#include <stdio.h>
#include <math.h>

#define STEP 10
#define EPS 0.0001

void print_header(FILE* stream_out){
  for (unsigned i = 0 ; i < 57 ; i++){
    fprintf(stream_out, "=");
  }
  fprintf(stream_out, "\nDegrees\t\tRadians\t\tsin(x)\t\tcos(x)\t\ttan(x)\t\tctan(x)\n");
  for (unsigned i = 0 ; i < 57 ; i++){
    fprintf(stream_out, "=");
  }
  fprintf(stream_out, "\n");
}

int main(){
  FILE* trig_out = fopen("trig.txt", "w");
  float radians, sine, cosine, tangent, cotangent;

  print_header(trig_out);

  for (float degrees = 0 ; degrees <= 360 ; degrees += STEP){
    radians = degrees * M_PI / 180;
    sine = sin(radians);
    cosine = cos(radians);
    tangent = tan(radians);

    fprintf(trig_out, "%7.1f\t\t%7.3f\t\t%6.3f\t\t%6.3f\t\t", degrees, radians, sine, cosine);

    if ( fabs(cosine) < EPS ){
      fprintf(trig_out, "   -  \t\t");
    }
    else {
      fprintf(trig_out, "%6.3f\t\t", tangent);
    }
    
    if ( fabs(sine) < EPS ){
      fprintf(trig_out, "   -  \n");
    }
    else {
      cotangent = 1/tangent;
      fprintf(trig_out, "%6.3f\n", cotangent);
    }
  }

  fclose(trig_out);

  return 0;
}
