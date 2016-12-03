#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include <stdint.h>
#include "time_lib.h"

int main(int argc, char** argv) {
    uint32_t time_start = 0;
    uint32_t time_end   = 0;

    int fd, offset;
    char *data;
    char r_data;
    struct stat sbuf;
    if ((fd = open("file.txt", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    if (stat("file.txt", &sbuf) == -1) {
        perror("stat");
        exit(1);
    }
    offset = 1;

    if ( (data = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == (caddr_t)(-1) ){
        perror("mmap");
        exit(1);
    }
    //should page fault here

    // char* file_data = (char*) malloc(sizeof(char) * sbuf.st_size);

    // time_start = rdtsc32();
    // //r_data = data[offset];
    // // memcpy(file_data, data, sbuf.st_size);
    // time_end   = rdtsc32();


//    printf("%c\n", r_data);
    // printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

    //check after to see if you still get a page fault
    time_start = rdtsc32();
    r_data = data[1000];
    time_end   = rdtsc32();

    printf("%c\n", r_data);
    printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

    return 0;
}
