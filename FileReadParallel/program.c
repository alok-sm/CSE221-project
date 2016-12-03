#define _GNU_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
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

    char* cache_clear_cmd = "sync; sudo sh -c \"echo 3 > /proc/sys/vm/drop_caches\"";

    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    uint32_t total   = 0;


    int BLKSIZE = 512000;
    if (argc < 2){
        printf("Usage - fname\n");
        exit(1);
    }
    
    int filedesc = open(argv[1], O_RDONLY | O_DIRECT);
    //char buf[5120];
    //int BLKSIZE = 512000;
    char *subblk = (char *) memalign(BLKSIZE, BLKSIZE);
    if(filedesc < 0){
        return 1;
    }
    int bytes_read, num_blks = 0;

    do{
        system(cache_clear_cmd);
        time_start = rdtsc32();
        bytes_read = read(filedesc, subblk, BLKSIZE);
        time_end   = rdtsc32();
        if (bytes_read < 0) {
            printf("error : %s\n", strerror(errno));
            exit(1);
        }
        if (bytes_read){
            total += time_end - time_start;
            num_blks += 1;
        }
    }while(bytes_read);
    //if (nbytes < 0) {
    //    printf("error : %s\n", strerror(errno));
    //    exit(1);
    //}
    printf("Data: %c\n ", subblk[0]);
    uint32_t per_btime = total/num_blks;
    double read_time = per_btime/(float)500000;
    printf("sequential time delta in cycles= %u\n",per_btime );
    printf("sequential time delta in ms= %llf\n", read_time );


    // random
    time_start = 0;
    time_end = 0;
    total = 0;
    int i;

    srand(time(NULL));
    int block_no;
    printf("num_blks = %d\n", num_blks);
    
    for(i = 0; i < num_blks; i ++){
        // printf("iteration %d\n", i);
        block_no = rand() % num_blks;
        lseek(filedesc, block_no * BLKSIZE, SEEK_SET);
        system(cache_clear_cmd);
        time_start = rdtsc32();
        bytes_read = read(filedesc, subblk, BLKSIZE);
        time_end   = rdtsc32();
        
        if (bytes_read < 0) {
            printf("error : %s\n", strerror(errno));
            exit(1);
        }
        if (bytes_read){
            total += time_end - time_start;
        }
    };
    //if (nbytes < 0) {
    //    printf("error : %s\n", strerror(errno));
    //    exit(1);
    //}
    printf("random Data: %c\n ", subblk[0]);
    per_btime = total/num_blks;
    read_time = per_btime/(float)500000;
    printf("random time delta in cycles= %u\n",per_btime );
    printf("random time delta in ms= %llf\n", read_time );






    return 0;
}
