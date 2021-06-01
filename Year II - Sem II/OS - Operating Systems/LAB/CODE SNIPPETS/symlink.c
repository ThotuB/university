unlink(new_path);
if( symlink(new_path, "my_link") )  {
    exit(8);
} 