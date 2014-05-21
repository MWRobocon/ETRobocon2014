//UDPServer.c
 
/*
 *  gcc -o UDPserver UDPServer.c
 *  ./server
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
#define BUFLEN 512
#define PORT 35713
 
void err(char *str)
{
    perror(str);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in my_addr, cli_addr;
    int sockfd, i;
    socklen_t slen=sizeof(cli_addr);
    uint8_t buf[BUFLEN];
 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
      err("socket");
    else
      printf("Server : Socket() successful\n");
 
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
      err("bind");
    else
      printf("Server : bind() successful\n");
 
    while(1)
    {
        if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
            err("recvfrom()");
        printf("Received packet from %s:%d\nData: %d\t%d\t%d\t%d\n\n",
               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf[0],buf[1],buf[2],buf[3]);
    }
 
    close(sockfd);
    return 0;
}
