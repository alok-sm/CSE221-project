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

int main(int argc, char** argv) {
	char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;

    time_start = rdtsc32();
    //sleep(10);
    time_end   = rdtsc32();

    printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

    return 0;
}
