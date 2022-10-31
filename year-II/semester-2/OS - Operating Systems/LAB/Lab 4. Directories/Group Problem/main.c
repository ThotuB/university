#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

/*
Un singur argument - cale catre director (eventual absoluta)

Verificam argument -> Usage %s path, argv[0]

Daca nu e director -> eroare

Parcurgem recursiv subarborele directorului
Afisam
    -Nr legaturi simbolice care indica spre fisiere obisnuite
*/

int findSymbolicLinks(char path[]) {

    int linkContor = 0;
    DIR *new_dir = opendir(path);
    
    if(new_dir == NULL) { 
        perror("Could not open the directory\n");
        exit(4);
    }

    char next_path[4096];
    struct dirent *dir_data;

    while( (dir_data = readdir(new_dir)) ) { //reading each entry

        if( (!strcmp(dir_data -> d_name, ".")) || (!strcmp(dir_data -> d_name, "..")) )
            continue; //skipping the inodes "." and ".."
        
        //d_name only contains the name so we update the path
        strcpy(next_path, path);
        strcat(next_path, "/");
        strcat(next_path, dir_data -> d_name); 

        //printf("%s\n", next_path ); //useful to see the files

        struct stat st;
        if( lstat(next_path, &st) < 0 ) {
            perror("Could not access the current file (bad path)\n");
            exit(5);
        }
        if( ( S_IFDIR == (st.st_mode & S_IFMT)) ) {
            linkContor += findSymbolicLinks(next_path); //recursively add the contors from each subdirectory
        }
        else {
            if( (S_IFLNK ==  (st.st_mode & S_IFMT)) ) { //if it's a symbolic link
                struct stat symLinkDereferenced;
                if( stat(next_path, &symLinkDereferenced) < 0 ) { //use stat to dereference it
                    perror("Could not access the dereferenced symbolic link\n");
                    exit(6);
                }

                if ( (S_IFREG == (symLinkDereferenced.st_mode & S_IFMT)) ){ //if it's a regular file
                    linkContor++;
                }
            }
        }   
    }

    closedir(new_dir);
    return linkContor;
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage %s path\n", argv[0] );
        exit(1);
    }

    struct stat st;
    if( lstat(argv[1], &st) < 0 ) {
        perror("Could not access\n");
        exit(2);
    }

    if( !( S_IFDIR == (st.st_mode & S_IFMT)) ) {
        perror("Not a directory\n");
        exit(3);
    }

    printf("Symbolic links that point to regular files: %d\n", findSymbolicLinks(argv[1]));

  return 0;
}