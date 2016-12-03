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

int main(){

    char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;


    int fd[2];
    pipe(fd);
    struct timespec tstart, tend;
    char str[1];

    int child_pid = fork();

    if(child_pid == 0){ //child
        close(fd[0]);

        
        time_start = rdtsc32();
        write(fd[1], "1", 1);
        read(fd[1], str, 1);
        
        time_end   = rdtsc32();

        printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

    }else{ //parent
        close(fd[1]);
        read(fd[0], str, 1);
        write(fd[0], "1", 1);
        exit(0);
    }

    return 0;
}