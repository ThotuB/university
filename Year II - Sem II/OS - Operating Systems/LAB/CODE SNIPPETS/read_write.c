//Read list of directories from file argv[1]
while ( (readErr = read(readFd, buff, buffSZ) != 0) ) {
    if (readErr < 0) {
        perror("Couldn't read a block");
        exit(4);
    }
    //printf("%s", buff);
    for (int i = 0 ; buff[i] ; i++) {

        line[contorL++] = buff[i];
        //printf("%s\n", line);


        if (line[contorL - 1] == '\n') {

            for (j = 0 ; !isspace(line[j]) ; j++); //getting strange characters like ASCII code 13 and 10 when reading "."

            line[j] = 0;
            //printf("%s %s %d\n", line, ".", strcmp(line, "."));
            //printf("%s %s %d\n", line, ".", strcmp(line, "."));
            fSize = checkDir(line);
            sprintf(writeBuffer + strlen(writeBuffer), "%s total size: %d\n", line, fSize);

            memset(line, 0 , buffSZ);
            contorL = 0;

        }

    }

    memset(buff, 0, buffSZ);
}