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
#include "serialPort_common.h" /*Common function shared by serialPort_serv and serialPort_client*/

void main(int argc, char *argv[])
{
    // Only need to collect data from Mario Princess and Yoshi
    char *dev_list[] = {"/dev/rfcomm1", "/dev/rfcomm2","/dev/rfcomm3"};
    uint16_t port_list[] = {35713, 35714, 35715};
    uint8_t enable_list[]  = {1, 0, 0};
    useconds_t probe_multiply = 100; /* In 10 milliseconds */
    size_t msgLength = 4; /* In bytes */
    //char dev_id []= {"/dev/rfcomm1"};
    if (argc==2){
        probe_multiply = (useconds_t) atoi(argv[1]);
    }
    
    if (argc==3){
        probe_multiply = (useconds_t) atoi(argv[1]);
        msgLength = (size_t)atoi(argv[2]);
    }
    
    if (argc==4){
        probe_multiply = (useconds_t) atoi(argv[1]);
        msgLength = (size_t)atoi(argv[2]);
        get_enable_list(atoi(argv[3]), 3, enable_list);
    }
    
    printf("Initiating data collection...\n");
    printf("Probe Interval: %d ms\n", probe_multiply*10);
    printf("Probe Message Length: %d bytes\n", msgLength);
    printf("Enable integer: %s\n",argv[3]);
    printf("Enable list:%d\t%d\t%d\n",enable_list[0],enable_list[1],enable_list[2]);
    
    uint8_t chout[64];
    if (msgLength>63){
        printf("Warning: The maximum length per message is 63 bytes...\n");
        msgLength = 63;
    }
    
    int mainfd[] = {-1,-1,-1};/* File descriptor */
    struct termios options[3];
    int count = 0;
    int recv_count = 0;
    
    struct sockaddr_in serv_addr[3];
    int sockfd[3];
    int slen=sizeof(serv_addr[1]);
    
    // Set up socket and UDP socket
    for (count=0;count<3;count++){
        if (enable_list[count]==0){
            // The device is not enabled
            continue;
        }else{
            mainfd[count] = open_port(dev_list[count],1);
            printf("serial port ID %d:%d\n",count,mainfd[count]);
            
            fcntl(mainfd[count], F_SETFL, FNDELAY);                  /* Configure port reading */
            /* Get the current options for the port */
            tcgetattr(mainfd[count], &options[count]);
            cfsetispeed(&options[count], B9600);                 /* Set the baud rates to 9600 */
            cfsetospeed(&options[count], B9600);
            
            /* Enable the receiver and set local mode */
            options[count].c_cflag |= (CLOCAL | CREAD);
            options[count].c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
            options[count].c_cflag &= ~CSTOPB; /* One stop bit */
            options[count].c_cflag &= ~CSIZE; /* No bit mask for data bit */
            options[count].c_cflag |=  CS8;                              /* Select 8 data bits */
            options[count].c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */
            
            /* Enable data to be processed as raw input */
            options[count].c_lflag &= ~(ICANON | ECHO | ISIG);
            
            /* Set the new options for the port */
            tcsetattr(mainfd[count], TCSANOW, &options[count]);
            // create UDP client
            if ((sockfd[count] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
                err("socket");
            
            bzero(&serv_addr[count], sizeof(serv_addr[count]));
            serv_addr[count].sin_family = AF_INET;
            serv_addr[count].sin_port = htons(port_list[count]);
            if (inet_aton("127.0.0.1", &serv_addr[count].sin_addr)==0)
            {
                fprintf(stderr, "inet_aton() failed\n");
                exit(1);
            }
        }
    }
    char garbage[800]; // Used to flush the buffer in serial one while serial two is open;
    //Flush out stale data
    for(count=0;count<3;count++){
            if (enable_list[count]==0){
                // The device is not enabled
                continue;
            }else{
                    read(mainfd[count], &garbage, 800*sizeof(uint8_t));
            }
    }
	int read_count = 0;
    /////////////////////////////////////////////
    // Collect data
    while (1)
    {
        for(count=0;count<3;count++){
            if (enable_list[count]==0){
                // The device is not enabled
                continue;
            }else if (mainfd[count]!=-1){
                /* Read 4 uint8_t value from serial port. The value is in following format
                 * |Message Legnth|0|mailbox ID|Message|, for example,
                 * 2 0 3 4, means the message contains two bytes(incl. mailbox ID),
                 * the message comes from mailbox #3 and the message is 4*/
                read(mainfd[count], &chout, msgLength*sizeof(uint8_t));          /* Read character from ABU */
                printf("serial read from user %d, data: %d\n",count, chout[3]);
                //Send data to UDP server
                //printf("Sending data from User %d, %d\t%d\t%d\t%d\t\n",count,chout[0],chout[1],chout[2],chout[3]);
                if (sendto(sockfd[count], &chout, msgLength*sizeof(uint8_t), 0, (struct sockaddr*)&serv_addr[count], slen)==-1)
                    err("sendto()");
            }
        }
		read_count++;
		if (read_count%100==0){
			//Flush the buffer every 100 read count
			for(count=0;count<3;count++){
				if (enable_list[count]==0){
					// The device is not enabled
					continue;
				}else{
						read(mainfd[count], &garbage, 400*sizeof(uint8_t));
				}
			}
		}
        usleep(10000*probe_multiply);// in micro seconds
    }
    // The following lines are not expected to be executed
    for(count=0;count<3;count++){
        if (enable_list[count]==0){
            // The device is not enabled
            continue;
        }
        /* Close the serial port */
        close(mainfd[count]);
        /* Close UDP socket */
        close(sockfd[count]);
    }
}
