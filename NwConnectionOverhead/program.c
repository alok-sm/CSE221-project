#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "time_lib.h"
#include <arpa/inet.h>

#define MYPORT 3490
#define SIZE_TO_SEND 1000
#define MY_IP "127.0.0.1"



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

    int sockfd, sockfd2;
    char tosend[16]; //a char (1byte) to send to receivers
    char ack[16];
    struct sockaddr_in my_addr,rcvr_addr;
    int sin_size = sizeof(my_addr), i, k, num_packet_sent, optval;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = inet_addr(MY_IP);
    memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));
    //allow reuse of port
    optval = 1;
 
    uint32_t time_start = 0;
    uint32_t time_end   = 0;
    uint32_t time_total = 0;


    time_start = rdtsc32();
    //open TCP socket,bind and accept RECEIVERS connections 
    if( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) ==-1){
     perror("socket error");
     exit(1);
    }
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int)) == -1) {
     perror("setsockopt");
     exit(1);
    }
    //bind(socketfd, struct about my address,sizeofmy address);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
     perror("bind");
     exit(1);
    }
    listen(sockfd,10);
    //send(sockfd2,&tosend,sizeof(char)*64,0);
    //sockfd2 = accept(sockfd, (struct sockaddr *)&rcvr_addr, &sin_size);
    //optval=recv(sockfd2,&ack,sizeof(char)*64,0);
    //close(sockfd2);
    close(sockfd);

    time_end = rdtsc32();
    printf("Connection overhead: %u\n", time_end - time_start);
    printf("Connection overhead: %llf\n", (time_end - time_start)/(float)500000);
    return 0;
}
