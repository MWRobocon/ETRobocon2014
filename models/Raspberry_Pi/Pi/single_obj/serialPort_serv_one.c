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
#include <signal.h> /*Definition ofr Unix signals */
#define SERVER_PORT 35712 /*Local port for listening*/
#define BUFLEN 63 /* Upperbound of receiving buffer */
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

uint8_t generate_msg(uint8_t* UDP_input, uint8_t* serial_output){
    
    // Extract mailbox ID
    uint8_t mailboxID = UDP_input[0];
    //send command is in 1XX level, the third number corresponds to mailboxID
    mailboxID = mailboxID%10;
    uint8_t msgLen = UDP_input[1]; /* Actual length of message body, the actual message sent out is with 2 addtional prefix byte (msgLen+1|0)*/
    if (msgLen>BUFLEN-3){
        printf("Warning: specified input length exceeds maximum message length(60 bytes), Only the first 60 bytes are going to be sent\n");
        msgLen = BUFLEN-3;
    }
    uint8_t count = 0;
    serial_output[0] = msgLen+1; /* message length include this byte itself*/
    serial_output[1] = 0; /* separator byte*/
    serial_output[2] = mailboxID;
    for (count=0;count<msgLen;count++){
        serial_output[3+count] = UDP_input[2+count];
    }
    return msgLen+3; // The actual message sent through serial port is message body plus 3 byte prefix (msgLen|0|mailbox ID)
}

void main()
{
    pid_t pid;
    
    int mainfd=0;                                            /* File descriptor for serial port*/
    int* serialfd_ptr = NULL;
    uint8_t chout[4];
    struct termios options;
    int count = 0;
    uint8_t serialMsg[BUFLEN]; /* First byte - message length, second byte - 0, message body follows*/
    //uint8_t serialMsg[]={2, 0, 3, 4};
    
    struct sockaddr_in serv_addr;
    int sockfd, i, slen=sizeof(serv_addr);
    
    struct sockaddr_in my_addr, cli_addr;
    int sockfd_serv;
    socklen_t slen_server=sizeof(cli_addr);
    uint8_t UDPbuf[BUFLEN]; /* First byte - cmd type, second byte message length, message body follows*/
    uint8_t collect_data = 0;
    uint8_t serial_msgLen = 0;
    uint8_t probe_interval = 0;
    char probe_interval_str[3];
    uint8_t probe_msgLen = 0;
    char probe_msgLen_str[3];
    int userID;
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
    while(1)
    {
        // recvfrom would pause until one UDP packet arrives
        if (recvfrom(sockfd_serv, UDPbuf, sizeof(UDPbuf), 0, (struct sockaddr*)&cli_addr, &slen_server)==-1){
            err("recvfrom()");
            printf("Received packet from %s:%d\nData: %d\t%d\t\n\n",
                    inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), UDPbuf[0],UDPbuf[1]);
        }
        if (UDPbuf[0]/100==2 && collect_data==0){
            // Init data collection if receive 2XX flag
            // Open serial port
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
            serial_msgLen = generate_msg(UDPbuf, serialMsg);
            //TODO: Need to send this message to all the devices
            /* Send initiate signal to BT device */
            write(mainfd,&serialMsg,serial_msgLen);
            // Get configuration for data collection process
            probe_interval = UDPbuf[serial_msgLen-1]; // UDP message is one byte less than serial message. sample time is appended at the end of message
            probe_msgLen = UDPbuf[serial_msgLen];
            // Convert to string
            sprintf(probe_interval_str,"%d",probe_interval);
            sprintf(probe_msgLen_str,"%d",probe_msgLen);
            printf("calling fork()\n");
            switch ((pid = fork()))
            {
                case -1:
                    /* Fork() has failed */
                    perror ("fork");
                    break;
                case 0:
                    /* This is processed by the child */
                    printf("Starting data collection child process...\n");
                    execl("./serialPort_test_conf", "./serialPort_test_conf", probe_interval_str, probe_msgLen_str, NULL);
                    printf("Uh oh! If this prints, execl() must have failed");
                    exit(EXIT_FAILURE);
                    break;
                default:
                    /* This is processed by the parent */
                    printf("This is a message from the parent\n");
                    collect_data=1;
                    int child_died,proc_status = 0;
                    while (1){
                        if (recvfrom(sockfd_serv, UDPbuf, sizeof(UDPbuf), 0, (struct sockaddr*)&cli_addr, &slen_server)==-1)
                            err("recvfrom()");
                        printf("Received packet from %s:%d\nData: %d\t%d\t\n\n",
                                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), UDPbuf[0],UDPbuf[1]);
                        if (UDPbuf[0]/100==1){
                            // Send message if receive 1XX flag
                            serial_msgLen = generate_msg(UDPbuf, serialMsg);
                            /* Write uint8_t value to serial port. The value is in following format
                             * |Message Legnth|0|mailbox ID|Message|, for example,
                             * 2 0 3 4, means the message contains two bytes(incl. mailbox ID),
                             * the message is setn to mailbox #3 and the message is 4*/
                            userID = (UDPbuf[0]-100)/10;
                            //TODO: Add user ID parser here
                            printf("Send to BT...\n");
                            serialfd_ptr = &mainfd;
                            write(serialfd_ptr[userID-1],&serialMsg,serial_msgLen);
                        }
                        /*
                    if (waitpid(0, &proc_status, WNOHANG) == 0){
                        printf("Children process died. Investigate why...\n");
                    }
                         */
                    }
                    // The following lines are not expected to be executed due to infinite loop
                    //Kill child process
                    kill(0, SIGTERM);
                    while (child_died==0)
                    {
                        printf("Check child status\n");
                        sleep(1);
                        if (waitpid(0, &proc_status, WNOHANG) == 0) child_died = 1;
                        if (child_died==0) kill(0, SIGKILL);
                    }
                    
                    /* Close the serial port */
                    close(mainfd);
                    /* Close UDP server socket*/
                    close(sockfd_serv);
                    break;
            }
        }
        
    }
    
}
