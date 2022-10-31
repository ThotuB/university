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

int main (int argc, char *argv[]) {
    open("data.txt", O_WRONLY | O_CREAT | O_TRUN,  );
}