#ifndef IPESSERVER_H
#define IPESSERVER_H

/* ~~~ could be common lib */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// !!! NETWORK LIBS
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>                                                                                                                                                                   #include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>


#define BUFF_SIZE 1024

/* That's mean that src/dst could be string with len5.
 That's mean that max connection for server is 5! = 120
 this parameter could be defined via get method from server */
#define FLD_SIZE 5

#define true 1
#define false 0
typedef char bool;
typedef unsigned char  us_int;

/* ~~~ end could be common lib */



#endif
