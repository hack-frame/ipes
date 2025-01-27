#ifndef IPES_DEFENITIONS_H
#define IPES_DEFENITIONS_H

#include "ipes_common.h"

#define BUFF_SIZE 1024

/* That's mean that src/dst could be string with len5.
 That's mean that max connection for server is 5! = 120
 this parameter could be defined via get method from server */
#define FLD_SIZE 5

#define true 1
#define false 0
typedef char bool;

struct Server_Data {
    struct sockaddr_in servaddr;
    int sock_fd;
    char * serv_ip;
    int serv_port;
    char buff[BUFF_SIZE];
    struct Ipes_msg * msg;
 };
 
struct Ipes_msg{
    char    src[FLD_SIZE];
    char    dst[FLD_SIZE];
    uint8_t size;
    /* ToDo this mechanism */
    uint8_t   msg_level;
    uint8_t   protocol_type;
    char      * data;
    char      * md5sum;
    struct Ipes_msg * next;
    struct Ipes_msg * prev;
};

#endif //IPES_DEFENITIONS_H 
