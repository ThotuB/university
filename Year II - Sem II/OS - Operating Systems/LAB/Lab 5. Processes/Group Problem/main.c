#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

unsigned print_divisors(const char *nrStr){
    char printString[1000] = "PID: ";
    sprintf(printString, "%s%d", printString, getpid());
    strcat(printString, " | NR: ");
    sprintf(printString, "%s%s", printString, nrStr);
    strcat(printString, " | DIVS: ");

    unsigned nr = atoi(nrStr);
    unsigned cnt = 1;
    for (unsigned i = 1 ; i <= nr/2 ; i++){
        if ( nr % i == 0 ){
            sprintf(printString, "%s%d ", printString, i);
            cnt++;
        }
    }
    sprintf(printString, "%s%s", printString, nrStr);

    printf("%s\n", printString);

    return cnt;
}

int main(int argc, char *argv[]){
    if ( argc < 4 ){
        printf("USAGE: %s file_name nr1 nr2 [nr3 ...]\n", argv[1]);
        exit(1);
    }

    // int pid = fork();
    // if ( pid < 0 ){
    //     perror("FORK ERROR");
    //     exit(2);
    // }
    // if ( pid == 0 ){
    //     execlp("wc", "wc", "-l", argv[1], NULL);
    //     perror("EXEC ERROR");
    //     exit(3);
    // }

    for (int i = 2 ; i < argc ; i++){
        int pid = fork();
        if ( pid < 0 ){
            perror("FORK ERROR");
            exit(2*i);
        }
        if ( pid == 0 ){
            unsigned divs = print_divisors(argv[i]);
            exit(divs);
        }
    }

    for (int i = 2 ; i < argc ; i++){
        int status;
        int pid = wait(&status);

        if ( pid < 0 ){
            perror("WAIT ERROR");
            exit(EXIT_FAILURE);
        }

        printf("Process <%d> exited with code <%d>\n", pid, WEXITSTATUS(status));
    }
}