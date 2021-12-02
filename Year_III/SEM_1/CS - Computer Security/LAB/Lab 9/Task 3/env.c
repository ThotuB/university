#include <unistd.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

extern char **environ;

void get_flags(char *argv[], int *e){
    for (int i = 1; argv[i] != NULL; i++){
        if (strcmp(argv[i], "-e") == 0){
            *e = true;
        }
    }
}

int main(int argc, char *argv[]) {
    char *args[2];

    bool e_flag = false;
    get_flags(argv, &e_flag);

    args[0] = "/usr/bin/env";
    args[1] = NULL;

    if (e_flag){
        execve(args[0], args, environ);
    } else {
        execve(args[0], args, NULL);
    }

    return 0;
}
