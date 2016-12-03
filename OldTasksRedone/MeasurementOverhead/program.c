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
    uint32_t temp   = 0;
    int i = 0;

    time_start = rdtsc32();

    for(i = 0; i < 10000; i ++){
        temp += rdtsc32();
    }
    time_end = rdtsc32();

    printf("%u\n", temp);

    printf("measurement overhead in cycles= %u\n", (time_end - time_start)/10000);
    printf("measurement overhead in ms= %llf\n", ((time_end - time_start)/10000)/(float)500000);

    time_start = rdtsc32();
    for (i = 0; i< 10000; i++);
    time_end = rdtsc32();

    printf("empty loop measurement overhead in cycles= %u\n", (time_end - time_start)/10000);
    printf("empty loop measurement overhead in ms= %llf\n", ((time_end - time_start)/10000)/(float)500000);
    return 0;
}
