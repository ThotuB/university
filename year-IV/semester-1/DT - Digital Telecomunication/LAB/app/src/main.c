#include <stdio.h>
#include <stdlib.h>

#include "../lib/Parser.h"

void parse(FILE* file) {
    uint32_t state = 0;

    while (1) {
        char current_char = fgetc(file);

        switch (parse_char(current_char, &state)) {
            case STATE_MACHINE_READY: {
                state = 0;
                printf("READY\n");
                return;
            }
            case STATE_MACHINE_ERROR: {
                state = 0;
                printf("PARSER ERROR\n");
                exit(1);
            }
            case STATE_MACHINE_NOT_READY: break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("error: wrong number of arguments\n");
        printf("usage: ./main.exe sample.txt\n");
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");

    if (file) {
        parse(file);
        fclose(file);
    }
    return 0;
}