#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    fork();
    //printf("%d\n", getpid());

    fork();
    //printf("%d\n", getpid());

    fork();
    printf("%d\n", getpid());

    exit(1);
}