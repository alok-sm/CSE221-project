#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "time_lib.h"

char *myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int fd[2];
char str[10];

void* fn(void* null){
    close(fd[1]);
    read(fd[0], str, 10);
    write(fd[0], "hahahahaha", 10);
    return NULL;
}

int main(){

    char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;


    pipe(fd);
    pthread_t k_thread;
    printf("In main\n");
    struct timespec tstart, tend;

    if(pthread_create(&k_thread, NULL, fn, NULL)) {
            fprintf(stderr, "Error creating thread\n");
            return 1;

    }
    printf("After creating thread\n");
    close(fd[0]);
    time_start = rdtsc32();
    write(fd[1], "1", 10);
    read(fd[1], str, 10);
    time_end   = rdtsc32();

    printf("After rw\n");
    if(pthread_join(k_thread, NULL)){
            return 2;
    }
    
    printf("time delta = %u\n", time_end - time_start);

    return 0;
}
