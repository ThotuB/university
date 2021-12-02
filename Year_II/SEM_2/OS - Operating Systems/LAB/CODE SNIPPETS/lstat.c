struct stat st;
if( lstat(argv[1], &st) < 0 ) {
    perror("Could not access\n");
    exit(2);
}

// stat(const char *file_name, struct stat *st)     inode
// lstat(const char *file_name, struct stat *st)    dereferenced inode

if( (S_IFDIR == (st.st_mode & S_IFMT)) )  // Dir
if( (S_IFLNK == (st.st_mode & S_IFMT)) )  // S link
if( (S_IFREG == (st.st_mode & S_IFMT)) )  // Regular file

//           S_IFMT     0170000   bit mask for the file type bit field

//           S_IFSOCK   0140000   socket
//           S_IFLNK    0120000   symbolic link
//           S_IFREG    0100000   regular file
//           S_IFBLK    0060000   block device
//           S_IFDIR    0040000   directory
//           S_IFCHR    0020000   character device
//           S_IFIFO    0010000   FIFO