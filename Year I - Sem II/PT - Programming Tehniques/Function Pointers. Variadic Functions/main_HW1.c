#include <stdio.h>
#include <stdarg.h>
#include <string.h>

unsigned max(unsigned a, unsigned b){
  return ( a > b ) ? a : b;
}

unsigned len(long long int nr){
  unsigned len = 0;
  while ( nr != 0 ){
    len++;
    nr /= 10;
  }
  return len;
}

void print_string(char *string, unsigned width, char just){
  unsigned len = strlen(string);
  if ( just == 'r' ){
    for ( ; width > len ; width--){
      putchar(' ');
    }
  }
  for ( ; (*string) != '\0' ; string++){
    putchar((*string));
  }
  if ( just == 'l' ){
    for ( ; width - len > 0 ; width--){
      putchar(' ');
    }
  }
}

void print_int(long long int nr, unsigned size, unsigned base, unsigned upper, unsigned width, char padding, char sign){
  int idigits[size+width];
  char cdigits[size+width];
  unsigned iter = size - 1;
  if ( nr < 0 ){
    sign = '-';
    nr *= -1;
  }

  for ( ; nr != 0 ; nr /= base){
    idigits[iter] = nr % base;
    if ( idigits[iter] < 10 ){
      cdigits[iter] = idigits[iter] + '0';
    }
    else {
      cdigits[iter] = idigits[iter] - 10 + 'a' - upper;
    }
    iter--;
  }
  if ( padding == ' ' ){
    cdigits[iter] = sign;
    iter--;
    for ( ; size - iter <= width ; iter--){
      cdigits[iter] = padding;
    }
    iter++;
  }

  if ( padding == '0' ){
    for ( ; size - iter < width ; iter--){
      cdigits[iter] = padding;
    }
    cdigits[iter] = sign;
  }

  for ( ; iter < size ; iter++){
    putchar(cdigits[iter]);
  }
}

void custom_printf(const char *format, ...){
  va_list args;
  va_start(args, format);
  int prnt_chars = 0;

  for ( ; (*format) != '\0' ; format++ ){
    if ( *format == '%' ){
      format++;
      /// FLAGS
      char justification = 'r';
      if ( (*format) == '-' ){
        justification = 'l';
        format++;
      }

      char sign = '0';
      if ( (*format) == '+' ){
        sign = '+';
        format++;
      }
      else if ( (*format) == ' ' ){
        sign = ' ';
        format++;
      }

      char padding = ' ';
      if ( (*format) == '0' ){
        padding = '0';
        format++;
      }

      /// WIDTH
      unsigned width = 0;

      while ( (*format) >= '0' && (*format) <= '9' ){
        width = width*10 + ( (*format) - '0' );
        format++;
      }
      if ( (*format) == '*' ){
        width = va_arg(args, unsigned);
        format++;
      }

      /// PRECISION
      unsigned precision = 0;

      if ( (*format) == '.' ){
        format++;
        while ( (*format) >= '0' && (*format) <= '9' ){
          precision = precision*10 + ( (*format) - '0' );
          format++;
        }
        if ( (*format) == '*' ){
          precision = va_arg(args, unsigned);
          format++;
        }
      }

      /// LENGTH
      unsigned length = 11;
      if ( (*format) == 'l' ){
        format++;
        if ( (*format) == 'l' ){
          length = 21;
          format++;
        }
      }
      if ( (*format) == 'l' ){
        length = 6;
        format++;
      }

      /// SPECIFIER
      if ( *(format) == 'd' || *(format) == 'i' ){
        print_int(va_arg(args, int), length, 10, 0, width, padding, sign);
      }
      else if ( *(format) == 'u' ){
        print_int(va_arg(args, unsigned), length, 10, 0, width, padding, sign);
      }
      else if ( *(format) == 'o' ){
        print_int(va_arg(args, unsigned), length, 8, 0, width, padding, sign);
      }
      else if ( *(format) == 'x' ){
        print_int(va_arg(args, unsigned), length, 16, 0, width, padding, sign);
      }
      else if ( *(format) == 'X' ){
        print_int(va_arg(args, unsigned), length, 16, 32, width, padding, sign);
      }
      else if ( *(format) == 'f' ){ // still need print_double
        printf("%f", va_arg(args, double));
      }
      else if ( *(format) == 'e' ){
        printf("%e", va_arg(args, double));
      }
      else if ( *(format) == 'g' ){
        printf("%g", va_arg(args, double));
      }
      else if ( *(format) == 'c' ){
        printf("%c", va_arg(args, int));
      }
      else if ( *(format) == 's' ){
        print_string(va_arg(args, char*), width, justification);
      }
      // else if ( *(format+1) == 'p' ){
      //   printf("%p", va_arg(args, ));
      //   format++;
      // }
      else if ( *(format) == 'n' ){
        *va_arg(args, int*) = prnt_chars;
      }
      else if ( *(format) == '%' ){
        putchar('%');
      }
      else {
        printf("ERROR");
      }
      prnt_chars++;
    }
    else{
      putchar(*format);
      prnt_chars++;
    }
  }
}

int main(){
  custom_printf("%+08d\n", 3321);
  printf("%+08d\n\n", 3321);
  custom_printf("%+08d\n", -3321);
  printf("%+08d\n\n", -3321);
  custom_printf("%-12s hmmmm\n", "gdfshfd");
  printf("%-12s hmmmm\n\n", "gdfshfd");
  custom_printf("%08x\n", 3321);
  printf("%08x\n\n", 3321);

  return 0;
}
