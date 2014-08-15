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
#include "serialPort_common.h"

int open_port(char* dev_id, uint8_t read_only)
{
    int fd;                                   /* File descriptor for the port */
    if (read_only>0)
        fd = open(dev_id, O_RDONLY | O_NOCTTY | O_NDELAY);
        /* The serial port is opened for read-only, we can replace O_RDONLY with O_RDWR
         * to open it in read-write mode
         */
    else{
        fd = open(dev_id, O_WRONLY | O_NOCTTY | O_NDELAY);
        /* The serial port is opened for write-only, we can replace O_WRONLY with O_RDWR
         * to open it in read-write mode
         */
    }
    if (fd == -1)
    {                                              /* Could not open the port */
        fprintf(stderr, "open_port: Unable to open %s - %s\n",
                dev_id, strerror(errno));
    }
    
    return (fd);
}

void get_enable_list(uint8_t input_integer, uint8_t search_length, uint8_t* enable_list){
    int count = 0;
    if (search_length>sizeof(enable_list)){
        search_length = sizeof(enable_list);
        printf("SerialPort_client: Search length exceeding length of enable list\n");
    }
    for(count=0;count<search_length;count++){
        enable_list[count] = input_integer & 0x01;
        input_integer = input_integer >> 1;
    }
}