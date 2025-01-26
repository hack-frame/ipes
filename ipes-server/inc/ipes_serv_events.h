#ifndef IPES_SERV_EVENTS_H
#define IPES_SERV_EVENTS_H

#include "ipes_defenitions.h"
#include "ipes_functions.h"

/*as argument should be path to conf file*/
struct Server_Data * init_serv(uint8_t ip_family, uint8_t socket_type, int port);
bool launch_serv(struct Server_Data * serv);

#endif

/*
struct Server_Data :
struct sockaddr_in servaddr;
int sock_fd;
char * serv_ip;
int serv_port;
char buff[BUFF_SIZE];
struct Msg_Data * msg;
*/
