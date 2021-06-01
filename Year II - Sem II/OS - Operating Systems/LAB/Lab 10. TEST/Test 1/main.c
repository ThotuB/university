#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define BUFFSIZE 4096

unsigned wsCount = 0;
unsigned secs = 0;

void child_proc_1(char *file, int pfd[2]){
    close(pfd[0]);

    dup2(pfd[1], 1);

    close(pfd[1]);

    execlp("cat", "cat", file, NULL);

    printf("EXEC ERROR");
}

void child_proc_2(int pfd[2]){
    close(pfd[1]);

    dup2(pfd[0], 0);

    close(pfd[0]);

    execlp("wc", "wc", "-c", NULL);

    printf("EXEC ERROR");
}

void count_whitespaces(int x){
    wsCount++;
}

void end_child_proc_3(int x){
    printf("<%d> white space characters were found\n", wsCount);
    exit(0);
}

void reset_alarm(int x){
    alarm(1);
    printf("After <%u> second(s), <%u> white space characters were found\n", ++secs, wsCount);
}

void child_proc_3(){
    struct sigaction action;
    memset(&action, 0x00, sizeof(struct sigaction));

    action.sa_handler = count_whitespaces;

    if (sigaction(SIGUSR1, &action, NULL) < 0 ){
        perror("SIGUSR1 ERROR");
        exit(-1);
    }

    action.sa_handler = end_child_proc_3;

    if (sigaction(SIGTERM, &action, NULL) < 0 ){
        perror("SIGTERM ERROR");
        exit(-1);
    }

    action.sa_handler = reset_alarm;

    if (sigaction(SIGALRM, &action, NULL) < 0 ){
        perror("SIGALRM ERROR");
        exit(-1);
    }

    alarm(1);

    while (1) { ; }
}

int main (int argc, char *argv[]) {
    if ( argc != 2 ){
        printf("USAGE %s file", argv[0]);
        exit(1);
    }

    int pid1;
    int pfd_1p[2];

    // PROCESS 1
    if ( pipe(pfd_1p) < 0 ) {
        perror("PIPE ERROR");
        exit(2);
    }

    if ( (pid1 = fork()) < 0 ){
        perror("FORK ERROR");
        exit(3);
    }
    if ( pid1 == 0 ){
        child_proc_1(argv[1], pfd_1p);
        exit(4);
    }

    // PROCCESS 2
    int pid2;
    int pfd_p2[2];

    if ( pipe(pfd_p2) < 0 ) {
        perror("PIPE ERROR");
        exit(2);
    }

    if ( (pid2 = fork()) < 0 ){
        perror("FORK ERROR");
        exit(3);
    }
    if ( pid2 == 0 ){
        close(pfd_1p[0]);
        close(pfd_1p[1]);
        child_proc_2(pfd_p2);
        exit(4);
    }

    // PROCCESS 3
    int pid3;

    if ( (pid3 = fork()) < 0 ){
        perror("FORK ERROR");
        exit(3);
    }
    if ( pid3 == 0 ){
        close(pfd_1p[0]);
        close(pfd_1p[1]);
        close(pfd_p2[0]);
        close(pfd_p2[1]);
        child_proc_3();
        exit(4);
    }

    /*
    // PARENT FOR PROCCESS 1
    close(pfd_1p[1]);

    int readChars;
    unsigned cnt = 0;
    char buffer[BUFFSIZE+1];
    char *bigBuffer = (char*)malloc(BUFFSIZE * sizeof(char));

    while ( (readChars = read(pfd_1p[0], buffer, BUFFSIZE)) ){
        if ( readChars < 0 ){
            printf("READ ERROR");
            exit(6);
        }

        memcpy(bigBuffer + cnt * BUFFSIZE, buffer, readChars);

        if ( readChars < BUFFSIZE ){
            bigBuffer[cnt * BUFFSIZE + readChars] = '\0';
            break;
        }

        cnt++;
        bigBuffer = (char*)realloc(bigBuffer, (cnt+1) * BUFFSIZE * sizeof(char));
    }

    close(pfd_1p[0]);

    // PARENT FOR PROCCESS 2 & 3
    close(pfd_p2[0]);

    cnt = 0;
    for (unsigned i = 0 ; bigBuffer[i] ; i++){
        if ( isspace(bigBuffer[i]) ){
            if ( kill(pid3, SIGUSR1) < 0 ){
                printf("SIGUSR ERROR");
                exit(8);
            }
        }
        else {
            buffer[cnt++] = bigBuffer[i];
            if ( cnt == BUFFSIZE ){
                write(pfd_p2[1], buffer, BUFFSIZE);
                cnt = 0;
                memset(buffer, '\0', BUFFSIZE);
            }
        }
    }
    write(pfd_p2[1], buffer, cnt);

    close(pfd_p2[1]);
    */

   close(pfd_1p[1]);
   close(pfd_p2[0]);

   int readChars;
   char buffer[1];

   while ( (readChars = read(pfd_1p[0], buffer, 1)) ) {
        if ( !isspace(buffer[0]) ) {
            if ( write(pfd_p2[1], &buffer[0], 1) < 0 ){
                printf("WRITE ERROR");
                exit(7);
            }
        }
        else {   
            if (kill(pid3, SIGUSR1) < 0) {
                printf("KILL ERROR");
                exit(8);
            }
        }
    }

    if ( kill(pid3, SIGTERM) < 0 ){
        printf("SIGTERM ERROR");
        exit(8);
    }

   close(pfd_1p[0]);
   close(pfd_p2[1]);

    int status;
    for (unsigned i = 0 ; i < 3 ; i++){
        int pid = wait(&status);

        if ( pid < 0 ){
            perror("WAIT ERROR");
            exit(9);
        }

        if ( !WIFEXITED(status) ){
            printf("EXIT ERROR?");
            exit(10);
        }

        printf("Child with PID <%d> ended with code <%d>.\n", pid, WEXITSTATUS(status));
    }

    //free(bigBuffer);

    return 0;
}