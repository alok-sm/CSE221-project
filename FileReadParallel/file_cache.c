#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>

 
int main(int argc, char **argv){

    char fname[20];
    int BLKSIZE = 0;
    if (argc < 3){
        printf("Usage - fname, size\n");
        exit(1);
    }
    else {
        fname = argv[1];
        BLKSIZE = atoi(argv[2]);
    }
    int filedesc = open(fname, O_RDONLY | O_DIRECT);
    //char buf[5120];
    //int BLKSIZE = 512000;
    char *subblk = (char *) memalign(BLKSIZE, BLKSIZE);
    if(filedesc < 0){
        return 1;
    }
    int nbytes = read(filedesc, subblk, BLKSIZE);
    if (nbytes < 0) {
        printf("error : %s\n", strerror(errno));
        exit(1);
    }
    printf("#bytes read :%d\nData: %s\n ", nbytes, subblk);
    return 0;
}
