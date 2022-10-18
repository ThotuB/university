#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/token.h"
#include "../lib/value.h"
#include "../lib/symbol.h"
#include "../lib/instruction.h"
#include "../lib/domain_analyzer.h"
#include "../lib/virtual_machine.h"

char *read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File not found\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *input = (char *)malloc(size + 1);
    if (fread(input, size, 1, fp) != 1) {
        printf("Error reading file_path\n");
        exit(1);
    }
    input[size] = '\0';

    fclose(fp);

    return input;
}

void run(const char *file_path) {
    char *file_name = (char *)malloc(sizeof(char) * 100);
    sprintf(file_name, "./res/%s", file_path);
    char *input = read_file(file_name);
    printf("%s\n", input);

    tokenize(input);
    analyzeDomain(token_list);
    run_vm(instructions);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./main.exe <file_path>\n");
        exit(1);
    }
    run(argv[1]);

    return 0;
}