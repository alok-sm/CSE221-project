#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include "time_lib.h"

char *myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void *some_func(void *time_end1){
    uint32_t *time_end = (uint32_t *)time_end1;
    *time_end = rdtsc32();
    return NULL;
}


int main(int argc, char** argv) {
	char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    uint32_t time_end1   = 0;
    pthread_t k_thread;

    time_start = rdtsc32();
    if(pthread_create(&k_thread, NULL, some_func, &time_end1)) {

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

    /* wait for the second thread to finish */ 
    if(pthread_join(k_thread, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    time_end = rdtsc32();

    printf("time delta in clock = %u\n", time_end - time_start);
    printf("time delta in ms = %llf\n", (time_end - time_start)/(float)500000);
    return 0;
}
