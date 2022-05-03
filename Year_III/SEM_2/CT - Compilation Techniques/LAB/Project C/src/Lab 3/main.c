#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/token.h"
#include "../../lib/lexical_analyzer.h"

int main() {
    // read file into string
    FILE *fp = fopen("../../res/input.c", "r");

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *input = (char *)malloc(size + 1);
    fread(input, size, 1, fp);
    input[size] = '\0';

    printf("%s\n", input);

    tokenize(input);
    showTokens();

    fclose(fp);

    return 0;
}