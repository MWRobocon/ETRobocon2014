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
#include "serialPort_common.h" /*Common function shared by serialPort_serv and serialPort_client*/
#include <pthread.h>
#define SERVER_PORT 35712 /*Local port for listening*/
#define BUFLEN 63 /* Upperbound of receiving buffer */


// pthread_mutex_t msg_mutex = PTHREAD_MUTEX_INITIALIZER;

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
    
    int mainfd[4];                                            /* File descriptor for serial port*/
    struct termios options[4];
    int count = 0;
    int user_id, cmd = 0;
    char *dev_list[] = {"/dev/rfcomm1", "/dev/rfcomm2","/dev/rfcomm3","/dev/rfcomm4"};
    uint8_t enable_list[]  = {1, 0, 0, 0};
    uint8_t serialMsg[BUFLEN]; /* First byte - message length, second byte - 0, message body follows*/
    
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
    char enable_list_str[3];
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
    while(1){
        // recvfrom would pause until one UDP packet arrives
        if (recvfrom(sockfd_serv, UDPbuf, sizeof(UDPbuf), 0, (struct sockaddr*)&cli_addr, &slen_server)==-1){
            err("recvfrom()");
            printf("Received packet from %s:%d\nData: %d\t%d\t\n\n",
                    inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), UDPbuf[0],UDPbuf[1]);
        }
        cmd = UDPbuf[0];
        if (cmd/100==2 && collect_data==0 && cmd!=200){
            // Init data collection if receive 2XX flag
            // Open serial port
            cmd -= 200; //Remove the 1st digit
            user_id = cmd/10;
            
            serial_msgLen = generate_msg(UDPbuf, serialMsg);
            // Get configuration for data collection process
            probe_interval = UDPbuf[serial_msgLen-1]; // UDP message is one byte less than serial message. sample time is appended at the end of message
            probe_msgLen = UDPbuf[serial_msgLen];
            get_enable_list(UDPbuf[serial_msgLen+1], 4, enable_list);
            
            for (count=0;count<4;count++){
                if (enable_list[count]==0){
                    // The device is not enabled
                    continue;
                }
                //sprintf(device_id,"%d",user_id);
                mainfd[count] = open_port(dev_list[count],0);// Open the port for write only
                
                fcntl(mainfd[count], F_SETFL, FNDELAY);                  /* Configure port reading */
                /* Get the current options for the port */
                tcgetattr(mainfd[count], &options[count]);
                cfsetispeed(&options[count], B9600);                 /* Set the baud rates to 9600 */
                cfsetospeed(&options[count], B9600);
                
                /* Enable the receiver and set local mode */
                options[count].c_cflag |= (CLOCAL | CREAD);
                options[count].c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
                options[count].c_cflag &= ~CSTOPB; /* One stop bit */
                options[count].c_cflag &= ~CSIZE;  /* No bit mask for data bits */
                options[count].c_cflag |=  CS8;                              /* Select 8 data bits */
                options[count].c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */
                
                /* Enable data to be processed as raw input */
                options[count].c_lflag &= ~(ICANON | ECHO | ISIG);
                
                /* Set the new options for the port */
                tcsetattr(mainfd[count], TCSANOW, &options[count]);                
            }
            for (count=0;count<4;count++){
                if (enable_list[count]==0){
                    // The device is not enabled
                    continue;
                }
                //TODO: Need to send this message to all the devices
                /* Send initiate signal to BT device */
                write(mainfd[count],&serialMsg,serial_msgLen);
            }
            
            // Spawn child process
            // Convert to string
            sprintf(probe_interval_str,"%d",probe_interval);
            sprintf(probe_msgLen_str,"%d",probe_msgLen);
            sprintf(enable_list_str,"%d",UDPbuf[serial_msgLen+1]);
            printf("calling fork()\n");
            switch ((pid = fork())){
                case -1:
                    /* Fork() has failed */
                    perror ("fork");
                    break;
                case 0:
                    /* This is processed by the child */
                    printf("Starting data collection child process...\n");
                    execl("/home/pi/bluetooth/serialPort_client_mp", "/home/pi/bluetooth/serialPort_client_mp", probe_interval_str, probe_msgLen_str, enable_list_str, NULL);
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
                        printf("Received packet from %s:%d\nData: %d\t%d\t%d\n\n",
                                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), UDPbuf[0],UDPbuf[1],UDPbuf[2]);
                        if (UDPbuf[0]/100==1){
                            userID = (UDPbuf[0]-100)/10;
                            if (enable_list[userID-1]!=0 && mainfd[count-1]!=-1){
                                
                                // Send message if receive 1XX flag
                                serial_msgLen = generate_msg(UDPbuf, serialMsg);
                                /* Write uint8_t value to serial port. The value is in following format
                                 * |Message Legnth|0|mailbox ID|Message|, for example,
                                 * 2 0 3 4, means the message contains two bytes(incl. mailbox ID),
                                 * the message is setn to mailbox #3 and the message is 4*/
                                //TODO: Add user ID parser here
                                printf("Send to user %d...\n",userID);
                                write(mainfd[userID-1],&serialMsg,serial_msgLen);
                            }
                        }else if (UDPbuf[0]==200){
                            // Bye signal, do the cleanup
                            //Kill child process
                            printf("Bye message received, stopping data collection...\n");
                            kill(pid, SIGTERM);
                            while (child_died==0)
                            {
                                printf("Check child status\n");
                                sleep(1);
                                if (waitpid(-1, &proc_status, WNOHANG) == 0) child_died = 1;
                                if (child_died==0) kill(pid, SIGKILL);
                            }
                            printf("Data collection stopped...\n");
                            collect_data = 0;
                            for(count=0;count<3;count++){
                                if (enable_list[count]==0){
                                    // The device is not enabled
                                    continue;
                                }
                                /* Close opened serial port */
                                close(mainfd[count]);
                            }
                            break; // Return to wait for init command
                        }
                        /*
                         * if (waitpid(-1, &proc_status, WNOHANG) == 0){
                         * printf("Children process died. Investigate why...\n");
                         * }
                         */
                    }
            }
        }        
    }
    // The following lines are not expected to be executed due to infinite loop
    /* Close UDP server socket*/
    close(sockfd_serv);    
}
