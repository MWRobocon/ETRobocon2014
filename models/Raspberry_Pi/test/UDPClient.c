//UDPClient.c

/*
 * gcc -o client UDPClient.c
 * ./client <server-ip>
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

//#define BUFLEN 512
#define PORT 35712

void err(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    int sockfd, i, slen=sizeof(serv_addr);
    //char buf[BUFLEN];
    uint8_t input_uint8[2];
    
    if(argc != 2)
    {
        printf("Usage : %s <Server-IP>\n",argv[0]);
        exit(0);
    }
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
    
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_aton(argv[1], &serv_addr.sin_addr)==0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    while(1)
    {
        printf("\nEnter data to send(Type 0 0 to exit) : ");
        //scanf("%[^\n]",buf);
        scanf("%d %d",&input_uint8[0], &input_uint8[1]);
        //getchar();
        if(input_uint8[0]==0&&input_uint8[1]==0)
            exit(0);
        
        if (sendto(sockfd, input_uint8, sizeof(input_uint8), 0, (struct sockaddr*)&serv_addr, slen)==-1)
            err("sendto()");
    }
    
    close(sockfd);
    return 0;
}
