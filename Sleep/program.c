#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "time_lib.h"

int main(int argc, char** argv) {
        uint32_t time_start = 0;
        uint32_t time_end   = 0;
        printf("pid = %d\n", getpid());
        sleep(10);
        printf("entering sleep\n");
        time_start = rdtsc32();
        sleep(1);
        time_end   = rdtsc32();

        printf("start = %u, end = %u, time delta = %u\n", time_start, time_end, time_end - time_start);

        return 0;
}
