#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <pthread.h>
#include <ctype.h>

int globalVar = 1;

int main (int argc, char *argv[]) {
    int localVar = 2;
    
    int pid;

    if ( (pid = fork()) == 0 ){
        globalVar = 3;
        localVar = 4;
        printf("CHILD: local <%d>\tglobal <%d>\n", localVar, globalVar);
        exit(1);
    }

    int status;
    wait(&status);

    printf("PARENT: local <%d>\tglobal <%d>\n", localVar, globalVar);
}