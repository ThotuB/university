#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define bool int
#define true 1
#define false 0

extern char **environ;

void printenv() {
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void get_flags(bool *c, bool *p, char *argv[]) {
    for (int i = 1; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            *c = true;
        } else if (strcmp(argv[i], "-p") == 0) {
            *p = true;
        }
    }
}

int main(int argc, char *argv[]) {
    pid_t childPid;

    bool c_flag = false;
    bool p_flag = false;
    get_flags(&c_flag, &p_flag, argv);

    switch (childPid = fork()) {
        case 0: /* child process */
            if (c_flag) {
                printenv();
            }
            exit(0);
        default: /* parent process */
            if (p_flag) {
                printenv();
            }
            exit(0);
    }
}
