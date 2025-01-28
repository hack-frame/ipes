#include <stdio.h>

#include "ipes_user.h"

int main(int argc, char **argv)
{
    struct Serv_Info * serv;
    if (argc != 2)
    {
        printf("parsing is not support right now\n");
        return (1);
    }
    parse_config(argv[2]);
    /* connect serv will be call for Unix and AFINET differently */
// HAVE to check it and re do code, maybe as 1 function, in struct use pointer not type
// serv = connect_to_unix_serv(AF_UNIX, SOCK_STREAM, NULL, 54545);
    serv = connect_to_serv(AF_INET, SOCK_STREAM, "192.168.0.108", 54545);
//  init_msg();
    if (!send_to_serv(serv, NULL)) // then instead NULL will be Ipes_msg * 
    {
        fprintf(stderr, "send to serv failed\n");
        return (EXIT_FAILURE);
    }
//  close_server_conn();
    printf("We did it\n");
    return (0);
}
