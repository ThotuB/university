#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<ctype.h>

/*

Please implement a C program, using system calls and library functions, that is run as follows:
 ./executable file, where file is a file path.

The program will verify whether there is one command-line argument. If it is not the case, it
 will display an error message showing the correct usage.

The parent process will create three child processes.

The first child process MUST run a command to send the contents of the file to the parent
 process.

The parent sends only those characters that are not white space characters to the second 
child process. For each white space character it finds, the parent process sends the SIGUSR1
 signal to the third child process.

The second child process MUST run a command to count the number of characters it receives
 and display the result.

The third child process counts the number of times it receives SIGUSR1 and runs until the
 parent process finishes sending the data to the second child process. When the third child ends,
it displays the total counter in the following format: “<N> white space characters were found” 
and sends the result back to the parent via the return code. In case execution takes more than 1 second,
every second intermediate results are displayed as follows: “After <x> second(s), <N> white space
characters were found”.

The parent process waits for all the child processes to end and displays the exit code for
 each child in the following format: “Child with PID <pid> ended with code <code>.”

The parent and child processes must run in parallel!

Please handle all error cases for system calls by displaying appropriate messages and
 terminating program execution.

The only library functions allowed for use are those for displaying and processing of
 characters and strings, and those for running commands.

Test files can be found here and here (a large file).

Good luck!

Cosmina

*/

#define BUFF_SIZE 4096

int count_child_3;
int counter_second;

void count_chars() {
    count_child_3++;
}

void stop_child3() {
    printf("<%d> white spaces were found !\n", count_child_3);
    exit(25);
}

void reset_alarm() {
    printf("After <%d> seconds, <%d> white spaces characters were found!\n", counter_second, count_child_3);
    alarm(1);
    counter_second++;
}

void third_child() {

    struct sigaction child3;
    memset(&child3, 0x00, sizeof(struct sigaction));

    child3.sa_handler = count_chars;
    if( sigaction(SIGUSR1, &child3, NULL ) < 0) {
        printf("Error at SIGUSR1!\n");
        exit(9);
    }

    child3.sa_handler = stop_child3;
    if( sigaction(SIGUSR2, &child3, NULL ) < 0) {
        printf("Error at SIGUSR2!\n");
        exit(9);
    }

    child3.sa_handler = reset_alarm;
    if( sigaction(SIGALRM, &child3, NULL ) < 0) {
        printf("Error at SIGUSR2!\n");
        exit(9);
    }

    alarm(1);

    // child 3 stops only when parent sends SIGUSR2
    while(1);
}

void second_child(int pfd2[]) {

    close(pfd2[1]);

    dup2(pfd2[0], 0);
    close(pfd2[0]);

    execlp("wc", "wc" , "-m", (char *) NULL);

    perror("The second execlp doesn't work!");
}

void first_child(char path[], int pfd1[]) {

    close(pfd1[0]);
    dup2(pfd1[1], 1);
    
    execlp("cat", "cat", path, (char *)NULL);

    perror("Error at first execlp!");
}

void parent(int pfd1[], int pfd2[],int pid3) {
    
    char buffer[BUFF_SIZE + 1];
    unsigned int readBytes = 0;

    //printf("PID3 IN FUNCTION: %d\n", pid3);

    while( (readBytes = read(pfd1[0], buffer, BUFF_SIZE)) ) {
        
        //printf("BUFFER: %s\n", buffer);
        for(unsigned int i = 0 ; i < readBytes; ++i) {
            if(!isspace(buffer[i]) ) {
                if(write(pfd2[1], &buffer[i], sizeof(char)) < 0) {
                    printf("Error at writing in main!\n");
                    exit(4);
                }
            }
            else {
                //printf("PID: %d\n", pid3);
                if(  kill(pid3, SIGUSR1) < 0 ){
                    printf("There was an error at kill!\n");
                    exit(11);
                }
            }
        }
    }
    close(pfd1[0]);
    close(pfd2[1]);

    if (kill(pid3, SIGUSR2) < 0) {
        printf("There was an error at the second kill!\n");
        exit(12);
    }
}

int main(int argc, char *argv[]) {

    if( argc != 2) {
        printf("Usage: <%s> <file> !\n",argv[0]);
        exit(1);
    }

    int pfd1[2], pfd2[2];
    pid_t pid1, pid2, pid3;

    if(pipe(pfd1) < 0) {
        perror("Error at pipe1!");
        exit(2);
    }

    if(pipe(pfd2) < 0) {
        perror("Error at pipe2!");
        exit(2);
    }

    if( (pid1 = fork()) < 0) {
        printf("There was an error at first fork!\n");
        exit(3);
    }

    if(!pid1) {     //child1 code
        close(pfd2[0]);
        close(pfd2[1]);
        first_child(argv[1], pfd1);
        close(pfd1[1]);
    }

    if( (pid2 = fork()) < 0) {
        printf("There was an error at second fork!\n");
        exit(3);
    }

    if(!pid2) {     //child2 code
        close(pfd1[0]);
        close(pfd1[1]);
        second_child(pfd2);
    }

    if( (pid3 = fork()) < 0) {
        printf("There was an error at third fork!\n");
        exit(3);
    }

    if(!pid3) {     // child3 code
        close(pfd2[0]);
        close(pfd2[1]);
        close(pfd1[0]);
        close(pfd1[1]);
       
        third_child();
    }

    // printf("pid3 in main: %d\n", pid3);
    // printf("pid2 in main: %d\n", pid2);
    // printf("pid1 in main: %d\n", pid1);

    //parent code

    close(pfd1[1]);
    close(pfd2[0]);

    parent(pfd1, pfd2, pid3);

    for(int i = 0 ; i < 3;  ++i) {
        int status;
        pid_t w = wait(&status);

        if(w == -1) {
            printf("Error at await!\n");
            exit(5);
        }

        if(WIFEXITED(status)) {
            printf("Child with PID: <%d> exited with code: %d\n", w, WEXITSTATUS(status));
        }
    }
    
    return 0;
}