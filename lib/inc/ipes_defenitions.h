#ifndef IPES_DEFENITIONS_H
#define IPES_DEFENITIONS_H

#include "ipes_common.h"

#define BUFF_SIZE 1024
#define DEFAULT_PORT 54545

/* That's mean that src/dst could be string with len5.
 That's mean that max connection for server is 5! = 120
 this parameter could be defined via get method from server */
#define FLD_SIZE 5

#if defined(__GNUC__) && !defined(__GNUG__)
    #define true 1
    #define false 0
    typedef char bool;
#endif

struct Serv_Info {
    struct sockaddr_in servaddr;
    char family_type;
    char sock_type;
    int sock_fd;
    int port;
    char * ip;
    char * user;
    char * password; 
    char buff[BUFF_SIZE];
    struct Ipes_msg * msg;
 };
 
struct Ipes_msg{
    char    src[FLD_SIZE];
    char    dst[FLD_SIZE];
    char size;
    /* ToDo this mechanism */
    char   msg_level;
    char   protocol_type;
    char      * data;
    char      * md5sum;
    struct Ipes_msg * next;
    struct Ipes_msg * prev;
};

#endif //IPES_DEFENITIONS_H 
