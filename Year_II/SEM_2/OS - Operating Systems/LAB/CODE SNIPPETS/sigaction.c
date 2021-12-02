struct sigaction p1;
memset(&p1, 0x00, sizeof(struct sigaction));

p1.sa_handler = alarm1;

if (sigaction(SIGALRM, &p1, NULL) < 0) {
    perror("Process a SIGALRM sigaction");
    exit(-1);
}