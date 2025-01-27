#ifndef IPES_USER_H
#define IPES_USER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipes_defenitions.h"
#include "ipes_functions.h"

struct  Server_Data * connect_to_serv(uint8_t ip_family, uint8_t socket_type, char * ip, int port);
struct  Server_Data * connect_to_unix_serv(uint8_t ip_family, uint8_t socket_type, char * path, int port);
struct  Msg_Data  * init_msg();
bool    send_to_serv();
bool    close_serv_conn();

#endif /* End IPES_USER_H  */
