#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int fd, offset;
    char *data;
    struct stat sbuf;
    if ((fd = open("data.txt", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    if (stat("data.txt", &sbuf) == -1) {
        perror("stat");
        exit(1);
    }
    offset = atoi(argv[1]);
    
    if ((data = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ){
        perror("mmap");
        exit(1);
    }

    int page_size = 4000;



    char* mem_data = (char*) malloc(page_size);
    char* destination = (char*) malloc(page_size);


    time_start = rdtsc32();
    memcpy(destination, data, page_size);
    time_end   = rdtsc32();

    printf("disk memcpy = %u\n", time_end - time_start);
    printf("%c\n", destination[1]);


    time_start = rdtsc32();
    memcpy(destination, mem_data, page_size);
    time_end   = rdtsc32();

    printf("mem  memcpy = %u\n", time_end - time_start);
    printf("%c\n", destination[1]);

    return 0;
}
