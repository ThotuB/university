#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <ctype.h>

unsigned child_process(DIR *dir, char *path, unsigned nr){
    char buffer[4096];
    
    char nextPath[4096];
    unsigned simlinks = 0;

    struct dirent *dir_data;
    while ( ( dir_data = readdir(dir)) ){
        if ( !strcmp(".", dir_data->d_name)  || !strcmp("..", dir_data->d_name) ){
            continue;
        }
        
        strcpy(nextPath, path);
        strcat(nextPath, "/");
        strcat(nextPath, dir_data->d_name);

        struct stat st;
        if ( stat(nextPath, &st) < 0 ){
            perror("BAD LINK");
            exit(7);
        }
        //if ( S_IFLNK == ( st.st_mode & S_IFMT )){ // doesn't work I think
            // need more checks for bytesize and regular files with lstat
            simlinks++;
            strcat(buffer, dir_data->d_name);
            strcat(buffer, "; ");
        //}
    }
    char fileName[4096];
    strcpy(fileName, path);
    strcat(fileName, "/Summary");

    int writeFD = open (fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);

    if (writeFD < 0) 
        exit(9);

    if( write(writeFD, buffer, strlen(buffer)) < 0)
        exit(10);

    if (close(writeFD) < 0)
        exit(11);

    exit(simlinks);

    return simlinks;
}

int main (int argc, char *argv[]) {
    if ( argc < 3 ) {
        printf("Usage: %s D dir1 dir2 ...", argv[0]);
        exit(1);
    }

    if ( argv[1][1] != '\0' ){
        printf("Argument 1 too long to be a digit");
        exit(2);
    }
    if ( !isdigit(argv[1][0]) ){
        printf("Argument 1 not a digit");
        exit(3);
    }

    unsigned totalSimlinks = 0;
    unsigned D = argv[1][0] - '0';
    unsigned realDirs = 0;

    for (unsigned i = 2 ; i < argc ; i++){
        struct stat st;
        if ( stat(argv[i], &st) < 0 ){
            continue;
        }
        if ( S_IFDIR != ( st.st_mode & S_IFMT )){
            continue;
        }

        DIR* dir = opendir(argv[i]);

        if ( dir == NULL ){
            continue;
        }

        realDirs++;

        int pid = fork();
        if ( pid < 0 ){
            perror("FORK ERROR");
            exit(4);
        }
        if ( pid == 0 ){
            //totalSimlinks += child_process(dir, argv[i], D); // doesn't work
            child_process(dir, argv[i], D);
            exit(5);
        }
    }

    for (unsigned i = 0 ; i < realDirs ; i++){
        int status;
        int pid = wait(&status);

        if ( pid < 0 ){
            perror("WAIT ERROR");
            exit(6);
        }

        printf("Child process <%d> ended with exit code <%d>\n", pid, WEXITSTATUS(status));
        totalSimlinks += WEXITSTATUS(status);
    }

    printf("Total simlinks: %u\n", totalSimlinks);

    return 0;
}