int status;
int w = wait(&status);

if ( w < 0 ) {
    perror("waitpid");
    exit(EXIT_FAILURE);
}

printf("Procesul <%d> s-a incheiat cu codul <%d> \n", w, WEXITSTATUS(status));