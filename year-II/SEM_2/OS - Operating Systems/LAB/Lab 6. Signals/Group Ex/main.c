#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int cpid;
int contor = 0;
double a = 0;
int swi;

void resetAlarm(int x) {
    alarm(1);
    printf("Parinte contor: %d\n", ++contor);
}

void processFinish(int n) {
    int status;
    pid_t w = wait(&status);
    
    if ( w == -1 ) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Last a value (rounded) encountered: %lf\n",(double) WEXITSTATUS(status)/100);

    swi = 1;
}

void parent(int n) {
    struct sigaction process_b;
    memset(&process_b, 0x00, sizeof(struct sigaction));

    process_b.sa_handler = resetAlarm;

    if (sigaction(SIGALRM, &process_b, NULL) < 0) {

        perror("Process a SIGALRM sigaction");
        exit(-1);

    }

    process_b.sa_handler = processFinish;
    if (sigaction(SIGCHLD, &process_b, NULL) < 0) {

        perror("Process a SIGCHLD sigaction");
        exit(-1);

    }

    alarm(1);
    
    for (int i = 0; ; i++) {
        printf("Inca procesez\n");

        if (contor == n) {
            if (kill(cpid, SIGUSR2) < 0) {

                printf("Error sending SIGUSR2 to child\n");
                exit(5);

            }

            break;
        }

        if (swi){
            break;
        }
    }
}

void killChildren (int hh) {
    printf("Child ended early!\n");
    exit((int)(a*100));
}

// void commandPrint (int n) {
//     printf("|\n");
// }

void child(int r) {
    struct sigaction process_child;
    memset(&process_child, 0x00, sizeof(struct sigaction));

    process_child.sa_handler = killChildren;

     if (sigaction(SIGUSR2, &process_child, NULL) < 0) {
        perror("Process a SIGUSR2 sigaction");
        exit(-1);
    }
   // process_child.sa_handler = commandPrint;

    // if (sigaction(SIGUSR1, &process_child, NULL) < 0) {
    //     perror("Process a SIGUSR2 sigaction");
    //     exit(-1);
    // }

    int contorSir = 0;

    while (contorSir < r) {

        printf("a[%d] = %lf\n", contorSir++, a);
        a = a + 1/(double)r;

    }

    exit((int)(a*100));

}

int main(int argc, char const *argv[]) {

    if (argc != 3) {

        printf("Usage: %s n, contor", argv[0]);
        exit(1);
    }

    if ((cpid = fork()) < 0) {
        perror("Couldn't fork");
        exit(2);
    }
    
    if (cpid == 0)
        child(atoi(argv[1]));
    else 
        parent(atoi(argv[2]));
    

    return 0;
}