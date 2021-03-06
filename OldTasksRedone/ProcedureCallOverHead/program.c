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

int some_func(){
   return 1;
}

int some_func1(int z){
    return z;
}

int some_func2(int a, int b){
    return a+b;
}

int some_func3(int a, int b, int c){
    return a+b+c;
}


int some_func4(int a, int b, int c, int d){
    return a+b+c+d;
}


int some_func5(int a, int b, int c, int d, int e){
    return a+b+c+d+e;
}


int some_func6(int a, int b, int c, int d, int e, int f){
    return a+b+c+d+e+f;
}


int some_func7(int a, int b, int c, int d, int e, int f, int g){
    return a+b+c+d+e+f+g;
}


int main(int argc, char** argv) {
	char* buf = (char*) malloc( 7 * sizeof(char) );
    char* cmd_base = "chrt -f -p 99 ";
    sprintf(buf, "%d", (int) getpid());
    char* cmd = myconcat(cmd_base, buf);
    system(cmd); 

    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    uint32_t total = 0;
    const int val = 9;
    int i = 0;

    time_start = rdtsc32();
    int ret = some_func();
    time_end   = rdtsc32();
    total = time_end - time_start;
    printf("0 time delta = %u\n", total);
    printf("0 time in ms = %llf\n", total/(float)500000);

    /*
    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func();
        time_end   = rdtsc32();
        printf("%u\n", (time_end - time_start));
        total += (time_end - time_start);
    }
    printf("0 time delta = %u\n", total/1000);
    printf("0 time in ms = %llf\n", (total/1000)/(float)500000);
    */
    /*
    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func1(val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("1 time delta = %u\n", total/1000);
    printf("1 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func2(val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("2 time delta = %u\n", total/1000);
    printf("2 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func3(val, val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("3 time delta = %u\n", total/1000);
    printf("3 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func4(val, val, val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("4 time delta = %u\n", total/1000);
    printf("4 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func5(val, val, val, val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("5 time delta = %u\n", total/1000);
    printf("5 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func6(val, val, val, val, val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("6 time delta = %u\n", total/1000);
    printf("6 time in ms = %llf\n", (total/1000)/(float)500000);

    total = 0;
    for (i=0; i < 1000; i++){
        time_start = rdtsc32();
        int ret = some_func7(val, val, val, val, val, val, val);
        time_end   = rdtsc32();
        total += (time_end - time_start);
    }
    printf("7 time delta = %u\n", total/1000);
    printf("7 time in ms = %llf\n", (total/1000)/(float)500000);

    */
    return 0;
}
