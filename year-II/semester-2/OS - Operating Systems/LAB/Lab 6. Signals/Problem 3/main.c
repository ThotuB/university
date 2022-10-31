#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int sw = 1;

void sendSIG1(int n) {
    if (kill(getppid(), SIGUSR1) < 0) {
        printf("Error sending SIGUSR1 to parent\n");
        exit(-1);
    }
}

void child(int a0, int r, long n) {
    struct sigaction p1;
    memset(&p1, 0x00, sizeof(struct sigaction));

    p1.sa_handler = sendSIG1;

    if (sigaction(SIGALRM, &p1, NULL) < 0) {
        perror("Process a SIGALRM sigaction");
        exit(-1);
    }

    alarm(1);

    long i = 0;
    double a = a0;

    while (i < n) {
        a = a + 1.0 / (double)r;
        // printf("%lf\n", a);
        i++;
    }

    printf("a[%ld] = %lf\n", n, a);
    exit(6);
}

char c = '*';

void changeC(int n) {
    c = '+';
}

void finishC(int n) {
    sw = 0;

    int status;
    pid_t w;

    w = wait(&status);

    if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Procesul <%d> s-a incheiat cu codul <%d> \n", w, WEXITSTATUS(status));
}

void parent() {
    struct sigaction p1;
    memset(&p1, 0x00, sizeof(struct sigaction));

    p1.sa_handler = changeC;

    if (sigaction(SIGUSR1, &p1, NULL) < 0) {
        perror("Process a SIGALRM sigaction");
        exit(-1);
    }

    p1.sa_handler = finishC;

    if (sigaction(SIGCHLD, &p1, NULL) < 0) {
        perror("Process a SIGALRM sigaction");
        exit(-1);
    }

    while (sw) {
        printf("%c\n", c);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s a0 r N \n", argv[0]);
        exit(1);
    }

    int pid;

    pid = fork();

    if (pid < 0) {
        perror("Couldnt fork");
        exit(1);
    }

    if (pid == 0)
        child(atoi(argv[1]), atoi(argv[2]), atol(argv[3]));

    parent();

    return 0;
}