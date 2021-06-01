#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


#define block 4096

int main (int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s, file_name dir\n", argv[0]);
        exit(1);
    }

    struct stat st;
    lstat(argv[2], &st);  //error handling !!

    if( !( S_IFDIR == (st.st_mode & S_IFMT)) ) {
      exit(4);
    }

    int fsize = st.st_size;
    int user_id = st.st_uid;

    printf("St_mode : %x\n", st.st_mode);
    
    char buffer[block] = {0};
    sprintf(buffer, "File Size: %d\nUser ID: %d\n", fsize, user_id);

    char new_path[block] = {0};
    strcpy(new_path, argv[2]);
    strcat(new_path, "/");
    strcat(new_path, argv[1]);
  
    int writeFD = open (new_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);

    if (writeFD < 0) 
        exit(5);

    if( write(writeFD, buffer, strlen(buffer)) < 0)
        exit(3);

    if (close(writeFD) < 0)
        exit(6);

    unlink(new_path);
    if( symlink(new_path, "my_link") )  {
      exit(8);
    }   

    return 0;
}