/*
 * This test program uses quasi-POSIX compliant UNIX functions to
 * open the serial port and read. The read message is forwarded to local 
 * UDP port 
 *
 * Uses termio functions to initialise the port to 9600 baud,
 * 8 bits/word, no parity, no hardware flow control,
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
#define PORT 35713 /**/

/*
 * 'open_port()' - Open serial port.
 *
 * Returns the file descriptor on success or -1 on error.
 */
int open_port(void)
{
    int fd;                                   /* File descriptor for the port */
    
    fd = open("/dev/rfcomm4", O_RDONLY | O_NOCTTY | O_NDELAY); /* The serial port is opened for read-only */
    
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
    
    struct sockaddr_in serv_addr;
    int sockfd, i, slen=sizeof(serv_addr);
      
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
    options.c_cflag &= ~CSIZE; /* No bit mask for data bit */
    options.c_cflag |=  CS8;                              /* Select 8 data bits */
    options.c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */
    
    /* Enable data to be processed as raw input */
    options.c_lflag &= ~(ICANON | ECHO | ISIG);
    
    /* Set the new options for the port */
    tcsetattr(mainfd, TCSANOW, &options);
    // create UDP client
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
    
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", &serv_addr.sin_addr)==0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    /////////////////////////////////////////////
    for (count=0;count<1000;count++)
    {
        /* Read 4 uint8_t value from serial port. The value is in following format
         * |Message Legnth|0|mailbox ID|Message|, for example,
         * 2 0 3 4, means the message contains two bytes(incl. mailbox ID), 
         * the message comes from mailbox #3 and the message is 4*/
        read(mainfd, &chout, sizeof(chout));          /* Read character from ABU */
        //Send data to UDP server
        if (sendto(sockfd, chout, sizeof(chout), 0, (struct sockaddr*)&serv_addr, slen)==-1)
            err("sendto()");
        usleep(1000000);// in micro seconds
    }
    /* Close the serial port */
    close(mainfd);
    /* Close UDP socket */
    close(sockfd);
}
