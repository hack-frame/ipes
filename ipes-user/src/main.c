#include <stdio.h>
#include <fcntl.h>

#include "ipes_user.h"
#include "ipes_parser.h"

struct Serv_Info * parse_config(char * path, char * unit)
{
    struct Serv_Info * serv;
    FILE * file;

    if (path == NULL || unit == NULL)
    {
        perror("file or unit name is not exist");
        return (NULL);
    } 
    if (!(serv = (struct Serv_Info *)malloc(sizeof(struct Serv_Info))))
    {
        perror("malloc in parser");
        return (NULL);
    }
    if (!(file = fopen(path, "r")))
    {
        perror("cannot open file");
        free(serv);
        return (NULL);
    }
    struct Unit_Block * unit_block = find_unit(file, unit);
    print_unit(unit_block);
/*
    if (!(serv->serv_ip = find_ip*(file, unit)))
    {
        perror("couldn't find ip");
        free(serv);
        return (NULL);
    }

    if(!(serv->serv_user = find_user(file, unit)))
    {
        perror("cannot find user");
        return (NULL);
    }
    if(!(serv->serv_password = find_password(file, unit)))
    {
        perror("cannot find password");
        return (NULL);
    }
*/
/*
    serv->serv_port = find_port(file, unit);
    serv->serv_user = find_user(file, unit);
    serv->family_type = find_family_type(file, unit);
    serv->socket_type = find_sock_type(file, unit);
 */
    return serv;
}

int main(int argc, char **argv)
{
    struct Serv_Info * serv;
    if (argc != 3)
    {
        printf("parsing is not support right now\n");
        return (1);
    }
    parse_config(argv[1], argv[2]);
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
