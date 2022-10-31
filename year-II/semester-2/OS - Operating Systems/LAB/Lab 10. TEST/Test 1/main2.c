#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>

#define CHILDREN 3

int contor;
int contorALARM;
int change = 1;

void errorCheck (char *s) {

    perror(s);
    exit(1);
}

void alarm1 (int sig) {

    alarm(1);
    contorALARM++;

    printf("After <%d> second(s) <%d> spaces were found\n", contorALARM, contor);
}

void increment(int sig) {

    contor++;
}

void changechange(int sig) {

    change = 0;
}

int pid1, pid2, pid3;

int main (int argc, char *argv[]) {

    if (argc !=2 ) {
        printf("Usage: %s file\n", argv[0]);
        exit(1);
    }

    int ch1ToParent[2];
    int parentToCh2[2];

    if (pipe (ch1ToParent) < 0) 
        errorCheck("pipe1");
    
    if (pipe (parentToCh2) < 0) 
        errorCheck("pipe2");

    pid1 = fork();

    if (pid1 < 0)
        errorCheck("fork1");
    
    //Child 1
    if (pid1 == 0) {

        close(ch1ToParent[0]);
        close(parentToCh2[0]);
        close(parentToCh2[1]);

        if (dup2(ch1ToParent[1], 1) < 0)
            errorCheck("dup2 from child 1");

        execlp("cat", "cat", argv[1], NULL);

        printf("Execlp error");

        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0)
        errorCheck("fork2");

    //Child 2
    if (pid2 == 0) {

        close (ch1ToParent[0]);
        close (ch1ToParent[1]);
        close (parentToCh2[1]);

        if (dup2 (parentToCh2[0], 0) < 0)
            errorCheck("dup2 fork2");

        //printf("Total bytes: \n"); 
        execlp("wc", "wc", "-c", NULL);
        
        printf("execlp err");

        exit(1);
    }

    pid3 = fork();

    if (pid3 < 0) 
        errorCheck("fork3");

    //Child 3
    if (pid3 == 0) {

        close(ch1ToParent[0]);
        close(ch1ToParent[1]);
        close(parentToCh2[0]);
        close(parentToCh2[1]);

        struct sigaction p1;
        memset(&p1, 0x00, sizeof(struct sigaction));

        p1.sa_handler = alarm1;
        if (sigaction(SIGALRM, &p1, NULL) < 0) 
            errorCheck("SIGALARM");

        p1.sa_handler = increment;
        if (sigaction(SIGUSR1, &p1, NULL) < 0)
            errorCheck("increment"); 

        p1.sa_handler = changechange;
        if (sigaction(SIGUSR2, &p1, NULL) < 0)
            errorCheck("change");

        alarm(1);

        while (change);

        printf("%d whitespaces were found\n", contor);

        exit(contor);
    }

    //Parent
    char buff[2] = {0}; //tailing 0 to always have a \0 in caz de orice

    int readbts;

    if (dup2 (ch1ToParent[0], 0) < 0)
        perror("dup2 parent");

    close(ch1ToParent[1]);
    close(parentToCh2[0]);

    while ( (readbts = read(ch1ToParent[0], buff, 1)) ) {
        
            //printf("%c", buff[0]);
            //usleep(1);
            if (!isspace(buff[0])) {
                if (write(parentToCh2[1], &buff[0], 1) < 0)
                    errorCheck("write parent to c2");
            }
            else {   
                if (kill(pid3, SIGUSR1) < 0) {
                    errorCheck("Kill sigusr1");
                }
            }
    }

    if (kill(pid3, SIGUSR2) < 0)
        errorCheck("Kill after su2");

    close(ch1ToParent[0]);
    close(parentToCh2[1]);

    for (int i = 0; i < CHILDREN; i++) {

        int status;
        pid_t w;

        w = wait(&status);

        if (w == -1)
            errorCheck("wait");

        int wxt = WEXITSTATUS(status);
        if (wxt < 0)
            errorCheck("wxt");

        printf("Child with PID <%d> ended with code <%d>\n", w, wxt);
    }
}