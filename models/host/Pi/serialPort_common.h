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

int open_port(char* dev_id, uint8_t read_only);
void get_enable_list(uint8_t input_integer, uint8_t search_length, uint8_t* enable_list);
typedef struct BT_UDP_INFO{
    int BT_fd;
    int UDP_fd;
    struct sockaddr_in serv_addr;
    size_t msgLength;
    useconds_t probe_multiply;
}BT_UDP_INFO;