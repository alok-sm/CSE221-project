#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "time_lib.h"

int main(int argc, char*argv[]) {
        uint32_t time_start = 0;
        uint32_t time_end   = 0;

        int size = atoi(argv[1]);
        int iterations = atoi(argv[2]);
        printf("size = %d, iterations = %d\n", size, iterations);
        int arr[size];
        int i, j = 0;

        for(i = 0; i < size; i ++){
            arr[i] = rand() % size;
        }

        time_start = rdtsc32();
        for(i = 0; i < iterations; i ++){
           // printf("itr -> %d\n", j);
            arr[j] = -arr[j];
            j = abs(arr[j]);
        }


        time_end   = rdtsc32();

        printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

        return 0;
}
