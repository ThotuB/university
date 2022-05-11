#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/token.h"
#include "../lib/domain_analyzer.h"

char *read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *input = (char *)malloc(size + 1);
    fread(input, size, 1, fp);
    input[size] = '\0';

    fclose(fp);

    return input;
}

int main() {
    // read file into string
    for (int i = 0; i < 1; i++) {
        // read file into string
        char *file_name = (char *)malloc(sizeof(char) * 100);
        sprintf(file_name, "../res/test%d.c", 0);
        printf("file_name: %s\n", file_name);
        char *input = read_file(file_name);

        printf("%s\n", input);

        tokenize(input);
        ruleCode();
    }

    return 0;
}