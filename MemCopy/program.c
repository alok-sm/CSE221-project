#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "time_lib.h"

#define R_ONE   time_start = rdtsc32(); \
                *iarr = iarr - arr; \
                time_end = rdtsc32(); \
                r_sum += time_end - time_start; \
                time_start = rdtsc32(); \
                sum += *iarr; \
                time_end = rdtsc32(); \
                w_sum += time_end - time_start; \
                iarr+= 100;

#define	R_FIVE		R_ONE R_ONE R_ONE R_ONE R_ONE
#define	R_TEN		R_FIVE R_FIVE
#define	R_FIFTY		R_TEN R_TEN R_TEN R_TEN R_TEN
#define	R_ONE_H		R_FIFTY R_FIFTY
#define R_FIVE_H	R_ONE_H R_ONE_H R_ONE_H R_ONE_H R_ONE_H 
#define R_1_K    	R_FIVE_H R_FIVE_H
#define R_5_K   	R_1_K R_1_K R_1_K R_1_K R_1_K
#define R_10_K   	R_5_K R_5_K
#define R_100_K     R_10_K R_10_K R_10_K R_10_K R_10_K R_10_K R_10_K R_10_K R_10_K R_10_K 
#define R_1_M       R_100_K R_100_K R_100_K R_100_K R_100_K R_100_K R_100_K R_100_K R_100_K R_100_K 

struct node {
    struct node *next;
    int val;
};

char *myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char** argv){

    char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd);

	int i = 0;
    int sum = 0;
    int r_sum = 0;
    int w_sum = 0;
	int len = 1000000;

    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    struct timespec tstart={0,0};
    struct timespec tend={0,0};

	char* arr = (char*) malloc(len * sizeof(char));
	char* iarr;

    iarr = arr;

    R_10_K


    printf("read cycles  = %u\n", r_sum/10000);
    printf("write cycles = %u\n", w_sum/10000);

    printf("sum = %ld\n", sum);

    return 0;
}
