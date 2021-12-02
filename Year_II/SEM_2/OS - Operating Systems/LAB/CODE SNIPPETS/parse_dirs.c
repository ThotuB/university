void parse_dir(char path[]) {

    int contor = 0;
    DIR *new_dir = opendir(path);
    
    if(new_dir == NULL) { 
        perror("Could not open the directory\n");
        exit(4);
    }

    char next_path[4096];
    struct dirent *dir_data;

    while( (dir_data = readdir(new_dir)) ) { //reading each entry

        if( (!strcmp(dir_data->d_name, ".")) || (!strcmp(dir_data->d_name, "..")) )
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

        if( S_IFDIR == (st.st_mode & S_IFMT) ) 
            parse_dir(next_path); //recursively add the contors from each subdirectory
        
        else {
            //Daca nu e director fa ce trb sa faci
         
        }   
    }

    closedir(new_dir);
}
