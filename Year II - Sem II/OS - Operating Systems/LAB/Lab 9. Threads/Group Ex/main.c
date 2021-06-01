#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>

unsigned Mat[10][10];
unsigned sums[10];
unsigned size;

void read_mat(char *fileName){
    FILE *fin = fopen(fileName, "r");

    for (unsigned i = 0 ; i < size ; i++){
        for (unsigned j = 0 ; j < size ; j++){
            fscanf(fin, "%d", &Mat[i][j]);
        }
    }
}

void print_mat(){
    for (unsigned i = 0 ; i < size ; i++){
        for (unsigned j = 0 ; j < size ; j++){
            printf("%d ", Mat[i][j]);
        }
        printf("\n");
    }
}

void *thread_sum(void *arg){
    unsigned index = *(unsigned*)arg;
    unsigned sum = 0;

    for (unsigned i = 0 ; i < size ; i++){
        sum += Mat[index][i];
    }

    printf("SUM: %u\n", sum);

    sums[index] = sum;

    pthread_exit(NULL);
}

int main(int argc, char **argv){
    printf("%d\n", argc);
    if ( argc != 3 ){
        printf("USAGE: %s <n> <file>\n", argv[0]);
        exit(1);
    }
    size = atoi(argv[1]);

    read_mat(argv[2]);
    print_mat();

    pthread_t tid[size];
    unsigned consts[10];

    for (unsigned i = 0 ; i < size ; i++){
        consts[i] = i;

        if ( pthread_create(&tid[i], NULL, thread_sum, (void*) &consts[i]) ){
            printf("THREAD ERROR");
            exit(1);
        }
    }

    unsigned BIGSUM = 0;
    for (unsigned i = 0 ; i < size ; i++){
        if ( pthread_join(tid[i], NULL) ){
            printf("JOIN ERROR");
            exit(2);
        }
        BIGSUM += sums[i];   
    }
    
    printf("BIG SUM: %u\n", BIGSUM);

    return 0;
}