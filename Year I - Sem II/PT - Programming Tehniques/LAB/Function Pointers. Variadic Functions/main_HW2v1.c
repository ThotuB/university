#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmpstringptr(const void *p1, const void *p2){
    char *nr1 = *(char**)p1;
    char *nr2 = *(char**)p2;

    printf("%s - %s\n", nr1, nr2);

    char nr1_sgn = ( nr1[0] == '-' ) ? '-' : '+';
    char nr2_sgn = ( nr2[0] == '-' ) ? '-' : '+';

    char *exp1 = strchr(nr1, 'e');
    char *exp2 = strchr(nr2, 'e');

    char exp1_sgn =  *(exp1 + 1);
    char exp2_sgn =  *(exp2 + 1);

    if ( nr1_sgn == nr2_sgn ){ // same sign
        if ( exp1_sgn == exp2_sgn ){ // same exponent sign
            if ( strlen(exp1) == strlen(exp2) ){ // same exponent length
                if ( strcmp( exp1 + 2, exp2 + 2 ) == 0 ){ // same exponent
                  if ( strcmp(nr1, nr2) == 0 ){
                    return 0;
                  }
                  printf("nr: %s - %s -> %d\n\n", nr1, nr2, strcmp(nr1, nr2));

                  return strcmp( exp1 + 2, exp2 + 2 );
                }
                printf("exp: %s - %s -> %d\n\n", exp1, exp2, strcmp(exp1, exp2));

                return strcmp( exp1 + 2, exp2 + 2 );
            }
            printf("exp len: %lu - %lu -> %d\n\n", strlen(exp1), strlen(exp2), ( exp1_sgn == '-' ) ? 2 * ( strlen(exp1) < strlen(exp2) ) - 1 : 2 * ( strlen(exp1) > strlen(exp2) ) - 1);

            return ( exp1_sgn == '-' ) ? 2 * ( strlen(exp1) < strlen(exp2) ) - 1 : 2 * ( strlen(exp1) > strlen(exp2) ) - 1;
        }
        printf("exp sng: %c - %c -> %d\n\n", exp1_sgn, exp2_sgn, (nr1_sgn == '-') ? 2 * ( exp1_sgn > exp2_sgn ) - 1 : 2 * ( exp1_sgn < exp2_sgn ) - 1);

        return (nr1_sgn == '-') ? 2 * ( exp1_sgn > exp2_sgn ) - 1 : 2 * ( exp1_sgn < exp2_sgn ) - 1;
    }
    printf("nr sgn: %c - %c -> %d\n\n", nr1_sgn, nr2_sgn, 2*(nr1_sgn < nr2_sgn )-1);

    return 2 * ( nr1_sgn < nr2_sgn ) - 1;

}

int main(int argc, char *argv[]){
    const char *floats[] = {"4.1234e23", "-4.1234e-23", "-4.1234e23", "4.1234e-23" };
    // if ( argc < 2 ){
    //     fprintf(stderr, "Usage: %s <string>...", argv[0]);
    //     exit(EXIT_FAILURE);
    // }
    //
    // qsort(&argv[1], argc - 1, sizeof(char*), cmpstringptr);
    //
    // for (int i = 1 ; i < argc ; i++){
    //     printf("%s ", argv[i]);
    // }
    // printf("\n");

    qsort(&floats[0], 4, sizeof(char*), cmpstringptr);

    for (int i = 0 ; i < 4 ; i++){
        printf("%s ", floats[i]);
    }

    return 0;
}
