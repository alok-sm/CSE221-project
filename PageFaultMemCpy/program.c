#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include "time_lib.h"

char *myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char *argv[]){
    char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    int fd, offset;
    char *data;
    struct stat sbuf;

    fd = open("data.txt", O_RDONLY);
    stat("data.txt", &sbuf);
    data = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    // printf("x\n");

    int page_size = 1000;

    uint32_t time_start = 0;
    uint32_t time_end   = 0;

    char* mem_data = (char*) malloc(page_size);
    char* destination = (char*) malloc(page_size);


    time_start = rdtsc32();
    memcpy(destination, data, page_size);
    time_end   = rdtsc32();

    printf("disk memcpy = %u\n", time_end - time_start);
    // printf("%c\n", destination[1]);


    time_start = rdtsc32();
    memcpy(destination, mem_data, page_size);
    time_end   = rdtsc32();

    printf("mem  memcpy = %u\n", time_end - time_start);
    // printf("%c\n", destination[1]);

    return 0;
}
