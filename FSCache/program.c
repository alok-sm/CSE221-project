#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "time_lib.h"

#define READ_SIZE 1

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

    int bytes = atoi(argv[1]);
    int fd = open("file.dat", O_RDONLY);
    int i, j, sum = 0, x;

    for (i = 0; i < bytes; ++i){
        read (fd, &x, 1);
        sum += x;
    }

    printf("%d\n", sum);

    lseek(fd, 0, SEEK_SET);

    time_start = rdtsc32();
    i = read (fd, &sum, 1);
    time_end   = rdtsc32();


    printf("%c\n", sum);

    if(i == 1){
        printf("delta = %u\n", time_end - time_start);
    }else{
        printf("read failed\n");
    }


    // time_start = rdtsc32();
    // bytes = read (fd, &buffer, READ_SIZE);
    // time_end   = rdtsc32();

    // if(bytes == READ_SIZE){
    //     printf("%u\n", time_end - time_start);
    // }else{
    //     printf("read failed\n");
    // }

    return 0;
}
