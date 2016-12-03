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

    char* sync_cmd = "sync"
    char* cache_drop_cmd = "sudo bash -c \"echo 3 > /proc/sys/vm/drop_caches\""

	char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* chrt_cmd = myconcat(cmd_base, buf);

    system(chrt_cmd); 
    system(sync_cmd); 
    system(cache_drop_cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;

    time_start = rdtsc32();
    sleep(10);
    time_end   = rdtsc32();

    printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

    return 0;
}
