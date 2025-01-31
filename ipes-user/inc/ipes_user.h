#ifndef IPES_USER_H
#define IPES_USER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipes_defenitions.h"
#include "ipes_functions.h"

bool connect_to_serv(struct Serv_Info * serv);
struct  Serv_Info * connect_to_unix_serv(char ip_family, char socket_type, char * path, int port);
struct  Msg_Data  * init_msg();
bool    send_to_serv();
bool    close_serv_conn();


struct Serv_Info * parse_config(char * path, char * unit);

#endif /* End IPES_USER_H  */
