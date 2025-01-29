#ifndef IPES_SERV_EVENTS_H
#define IPES_SERV_EVENTS_H

#include "ipes_defenitions.h"
#include "ipes_functions.h"

/*as argument should be path to conf file*/
struct Serv_Info * init_serv(char ip_family, char socket_type, int port);
bool launch_serv(struct Serv_Info * serv);

#endif

