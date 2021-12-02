int pid = fork();

if (pid < 0) {
    perror("Couldnt fork");
    exit(1);
}

if (pid == 0) {
    child();
    exit(getpid());
}

parent();