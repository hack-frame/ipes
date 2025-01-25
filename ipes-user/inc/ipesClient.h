#ifndef IPESCLIENT_H
#define IPESCLIENT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipesDefenitions.h"
#include "ipesFunctions.h"

struct	Server_Data * init_server(us_int ip_family, us_int socket_type, char * ip, int port);
struct	Msg_Data  * init_msg();
bool  	connect_to_serv();
bool 	send_to_serv();
bool 	close_serv_conn();

#endif /* End IPESCLIENT_H  */
