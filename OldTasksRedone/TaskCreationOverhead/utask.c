#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "time_lib.h"

char *myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int main(int argc, char** argv) {
	char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    int pid, wpid;
    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    uint32_t time_end1   = 0;
    int status = 0;
    time_start = rdtsc32();
    pid = fork();
    while ((wpid = wait(&status)) > 0);
    time_end   = rdtsc32();

    printf("time delta in clock cycles = %u pid = %d\n", time_end - time_start, pid);
    printf("time delta in ms = %llf pid = %d\n", (time_end - time_start)/(float)500000, pid);
    printf("pid = %d, wpid = %d, status = %d\n", pid, wpid, status);

   return 0;
}
