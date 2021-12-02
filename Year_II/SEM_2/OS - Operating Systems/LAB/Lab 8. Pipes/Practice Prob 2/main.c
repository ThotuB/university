#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define BUFSIZE 4096

void child_proc(int pfd_i[2], int pfd_o[2]){
    close(pfd_i[1]);
    close(pfd_o[0]);

    char *buffer = (char*)malloc(BUFSIZE * sizeof(char));
    char *bigBuffer = (char*)malloc(BUFSIZE * sizeof(char));
    int readChars;
    unsigned cnt = 0;

    while ( (readChars = read(pfd_i[0], buffer, BUFSIZE)) ) {
        memcpy(bigBuffer + cnt * BUFSIZE, buffer, readChars);

        if ( readChars < BUFSIZE ){ 
            bigBuffer[cnt * BUFSIZE + readChars] = '\0';
            break; 
        }

        cnt++;
        bigBuffer = (char*)realloc(bigBuffer, (cnt + 1) * BUFSIZE * sizeof(char));
    }

    unsigned cPos = 0;
    cnt = 0;

    char **numArgs = (char**)malloc(sizeof(char*));
    numArgs[cnt] = (char*)malloc(20 * sizeof(char));

    for (unsigned i = 0 ; bigBuffer[i] ; i++){
        if ( bigBuffer[i] <= '9' && bigBuffer[i] >= '0' ){
            numArgs[cnt][cPos++] = bigBuffer[i];
        }
        else if ( cPos != 0 ){
            numArgs[cnt][cPos] = '\0';
            cPos = 0;

            cnt++;
            numArgs = (char**)realloc(numArgs, (cnt + 1) * sizeof(char*));
            numArgs[cnt] = (char*)malloc(20 * sizeof(char));
        }
    }
    
    numArgs[cnt] = NULL;

    for (unsigned i = 0 ; i < cnt ; i++){
        //printf("%s\n", numArgs[i]);
    }

    dup2(pfd_o[1], 1);

    close(pfd_i[0]);
    close(pfd_o[1]);

    execvp("./script.sh", numArgs);

    printf("EXEC ERROR");
}

int main (int argc, char *argv[]) {
    if ( argc != 2 ) {
        printf("Usage: %s file", argv[0]);
        exit(1);
    }

    // FILE HANDLING
    int fd;

    if ( (fd = open(argv[1], O_RDONLY)) < 0 ){
        perror("FILE OPEN ERROR");
        exit(5);
    }

    // PIPE HANDLING
    int pfd1[2], pfd2[2];

    if ( pipe(pfd1) < 0 ){
        perror("PIPE ERROR");
        exit(1);
    }
    if ( pipe(pfd2) < 0 ){
        perror("PIPE ERROR");
        exit(1);
    }

    // FORKING
    int pid;

    if ( (pid = fork()) < 0 ){
        perror("FORK ERROR");
        exit(2);
    }
    if ( pid == 0 ){    // CHILD PROCESS
        child_proc(pfd1, pfd2);
    }

    // PARENT PROCESS
    close(pfd1[0]);
    close(pfd2[1]);

    char buffer[BUFSIZE+1];
    int readChars;

    // PRINT TO CHILD
    while ( (readChars = read(fd, buffer, BUFSIZE)) ) {
        if ( readChars < 0 ) {
            perror("READ ERROR");
            exit(4);
        }

        if ( write(pfd1[1], buffer, readChars) < 0 ){
            perror("WRITE ERROR");
            exit(4);
        }
    }

    if ( close(fd) < 0 ){
        perror("FILE CLOSE ERROR");
        exit(6);
    }
    
    close(pfd1[1]);

    int status;
    if ( (pid = wait(&status)) < 0 ){
        perror("WAIT ERROR");
        exit(7);
    }

    // PRINT FROM CHILD
    while ( (readChars = read(pfd2[0], buffer, BUFSIZE)) ) {
        if ( readChars < 0 ) {
            perror("READ ERROR");
            exit(4);
        }
        buffer[readChars] = '\0';
        printf("%s", buffer);
    }

    close(pfd2[0]);

    return 0;
}