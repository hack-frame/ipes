#ifndef IPESCLIENT_H
#define IPESCLIENT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// !!! NETWORK LIBS
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>


/* ~~~ could be common lib */
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

struct Server_Data {
	struct sockaddr_in servaddr;
	int sock_fd;
	char * serv_ip;
	int serv_port;
	char buff[BUFF_SIZE];
	struct Msg_Data * msg;
};

struct Msg_Data{
	char 		src[FLD_SIZE];
	char 		dst[FLD_SIZE];
	short int 	size;
	/* ToDo this mechanism */
	short int 	msg_level;
	short int	protocol_type;
	char 	  *	data;
	char 	  * md5sum;	
};

struct	Server_Data * init_server(us_int ip_family, us_int socket_type, char * ip, int port);
struct	Msg_Data  * init_msg();
bool  	connect_to_serv();
bool 	send_to_serv();
bool 	close_serv_conn();

/*additional functions*/
void fast_exit(char * msg);

#endif /* End IPESCLIENT_H  */
