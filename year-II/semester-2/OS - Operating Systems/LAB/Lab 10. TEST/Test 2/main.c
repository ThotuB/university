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

typedef struct data {
    char *path;
    unsigned index;
}data_t;

data_t newData(char *dir, char *file, unsigned index){
    data_t data;

    data.path = malloc(300 * sizeof(char));
    strcpy(data.path, dir);
    strcat(data.path, "/");
    strcat(data.path, file);

    data.index = index;

    return data;
}

unsigned counts[20];

void concat_chars_into_strings(char c, int* char_index, int* string_index, char strings[20][200]){
    if ( isspace(c) ){
        strings[*string_index][*char_index] = '\0';
        (*string_index)++;
        (*char_index) = 0;
    }
    else {
        strings[*string_index][*char_index] = c;
        (*char_index)++;
    }
}

void child_process_1(char *dir, int pfd[]){
    close(pfd[0]);

    dup2(pfd[1], 1);

    close(pfd[1]);

    execlp("ls", "ls", dir, NULL);
    
    printf("EXEC ERROR");
}

void *thread(void* arg){
    data_t data = *(data_t*)arg;

    int fd = open(data.path, O_RDONLY);
    if ( fd < 0 ){
        printf("OPEN ERROR");
        exit(5);
    }

    int readChars;
    char buffer[1];

    unsigned count = 0;
    while ( (readChars = read(fd, buffer, 1)) ){
        if ( readChars < 0 ){
            printf("READ ERROR");
            exit(6);
        }
        if ( isupper(buffer[0]) ){
            count++;
        }
    }

    close(fd);

    counts[data.index] = count;

    pthread_exit(NULL);
}

void child_process_2(char *dir, int N, int pfd[], int pfd2[]){
    close(pfd[1]);
    close(pfd2[0]);

    int readChars;
    char buffer[1];

    int char_index = 0;
    int string_index = 0;
    char strings[20][200];

    while ( (readChars = read(pfd[0], buffer, 1)) ){
        concat_chars_into_strings(buffer[0], &char_index, &string_index, strings);
    }

    pthread_t tid[20];
    data_t data[20];

    for (unsigned i = 0 ; i < string_index ; i++){
        data[i] = newData(dir, strings[i], i);
        pthread_create(&tid[i], NULL, thread, (void *) &data[i]);
    }

    for (unsigned i = 0 ; i < string_index ; i++){
        if ( pthread_join(tid[i], NULL) < 0 ) {
            printf("JOIN ERROR");
        }
        printf("File <%s> has <%u> capital letters\n", strings[i], counts[i]);

        if ( counts[i] > N ){
            if ( write(pfd2[1], strcat(strings[i], "\n"), strlen(strings[i]) + 1) < 0 ){
                printf("WRITE ERROR");
                exit(7);
            }
        }
    }

    close(pfd[0]);
    close(pfd2[1]);
}

int main(int argc, char *argv[]) {
    if ( argc != 3 ) {
        printf("Usage: %s N dir", argv[0]);
        exit(1);
    }

    int pid1, pid2;
    int pfd_12[2], pfd_2p[2];

    // CHILD PROCESS 1
    if ( pipe(pfd_12) < 0 ){
        printf("PIPE ERROR");
        exit(4);
    }

    if ( (pid1 = fork()) < 0 ){
        printf("FORK ERROR");
        exit(2);
    }
    if ( pid1 == 0 ){
        child_process_1(argv[2], pfd_12);
        exit(3);
    }

    // CHILD PROCESS 2
    if ( pipe(pfd_2p) < 0 ){
        printf("PIPE ERROR");
        exit(4);
    }

    if ( (pid2 = fork()) < 0 ){
        printf("FORK ERROR");
        exit(2);
    }
    if ( pid2 == 0 ){
        child_process_2(argv[2], atoi(argv[1]), pfd_12, pfd_2p);
        exit(3);
    }

    // PARENT PROCESS
    close(pfd_12[0]);
    close(pfd_12[1]);

    close(pfd_2p[1]);

    int readChars;
    char buffer[1];

    unsigned count = 0;
    while ( (readChars = read(pfd_2p[0], buffer, 1)) ){
        printf("%c", buffer[0]);
        if ( buffer[0] == '\n' ){
            count++;
        }
    }

    printf("Files received: %u\n", count);

    close(pfd_2p[0]);

    int status;
    for (unsigned i = 0 ; i < 2 ; i++){
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

    return 0;
}