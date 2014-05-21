/*
 * This test program uses quasi-POSIX compliant UNIX functions to read from
 * local UDP port. Once a UDP message is received, it would process the 
 * message. If needed, it would open the serial port and write to it.
 *
 * Uses termio functions to initialise the port to 9600 baud, at
 * 8 data bits, no parity, no hardware flow control,
 * and features character buffering.
 *
 * This program was derived from the example at
 * http://slackware.mirror.ac.za/slackware-7.0/docs/Linux-mini-HOWTO/Serial-Port-Programming
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <inttypes.h> /* uint8_t definition */
#include <arpa/inet.h> /* Definitions for internet operations*/
#include <netinet/in.h> /*Internet address family definition*/
#include <sys/types.h> /*System data type definition */
#include <sys/socket.h> /*Socket header*/
#include <stdlib.h> /* Standard library definitions */
#define SERVER_PORT 35712 /*Local port for listening*/
/*
 * 'open_port()' - Open serial port.
 *
 * Returns the file descriptor on success or -1 on error.
 */
int open_port(void)
{
    int fd;                                   /* File descriptor for the port */
    
    fd = open("/dev/rfcomm4", O_WRONLY | O_NOCTTY | O_NDELAY); 
    /* The serial port is opened for write-only, we can replace O_WRONLY with O_RDWR
     * to open it in read-write mode
     */    
    if (fd == -1)
    {                                              /* Could not open the port */
        fprintf(stderr, "open_port: Unable to open /dev/rfcomm4 - %s\n",
                strerror(errno));
    }
    
    return (fd);
}

void main()
{
    int mainfd=0;                                            /* File descriptor */
    uint8_t chout[4];
    struct termios options;
    int count = 0;
    int recv_count = 0;
    uint8_t msg1[]={2, 0, 3, 4};
    
    struct sockaddr_in serv_addr;
    int sockfd, i, slen=sizeof(serv_addr);
    
    struct sockaddr_in my_addr, cli_addr;
    int sockfd_serv;
    socklen_t slen_server=sizeof(cli_addr);
    uint8_t buf[4];
    uint8_t collect_data = 0;
    
    mainfd = open_port();
    
    fcntl(mainfd, F_SETFL, FNDELAY);                  /* Configure port reading */
    /* Get the current options for the port */
    tcgetattr(mainfd, &options);
    cfsetispeed(&options, B9600);                 /* Set the baud rates to 9600 */
    cfsetospeed(&options, B9600);
    
    /* Enable the receiver and set local mode */
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
    options.c_cflag &= ~CSTOPB; /* One stop bit */
    options.c_cflag &= ~CSIZE;  /* No bit mask for data bits */
    options.c_cflag |=  CS8;                              /* Select 8 data bits */
    options.c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */
    
    /* Enable data to be processed as raw input */
    options.c_lflag &= ~(ICANON | ECHO | ISIG);
    
    /* Set the new options for the port */
    tcsetattr(mainfd, TCSANOW, &options);
    /* Send initiate signal to device */
    write(mainfd,&msg1,sizeof(msg1));
    
    //create UDP server    
    if ((sockfd_serv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
    else
        printf("Server : Socket() successful\n");
    
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVER_PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd_serv, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
        err("bind");
    else
        printf("Server : bind() successful\n");
    
//////////////////////////////////////////////////////
    for (count=0;count<1000;count++)
    {          
        // recvfrom would pause until one UDP packet arrives 
        if (recvfrom(sockfd_serv, buf, sizeof(buf), 0, (struct sockaddr*)&cli_addr, &slen_server)==-1)
            err("recvfrom()");
        printf("Received packet from %s:%d\nData: %d\t%d\t\n\n",
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf[0],buf[1]);
        if (buf[0]/100==2){
            // Init data collection if receive 2XX flag
            collect_data=1;
        }
        if (buf[0]/100==1){
            // Send message if receive 1XX flag 
            msg1[3] = buf[1];
            /* Write 4 uint8_t value to serial port. The value is in following format
             * |Message Legnth|0|mailbox ID|Message|, for example,
             * 2 0 3 4, means the message contains two bytes(incl. mailbox ID),
             * the message is setn to mailbox #3 and the message is 4*/
            printf("Send to BT...\n");
            write(mainfd,&msg1,sizeof(msg1));
        }
    }
    /* Close the serial port */
    close(mainfd);
    /* Close UDP server socket*/
    close(sockfd_serv);
}
