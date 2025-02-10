#include <stdio.h>
#include <fcntl.h>

#include "ipes_user.h"
#include "ipes_parser.h"

struct Serv_Info * parse_config(char * path, char * unit)
{
    struct Serv_Info * serv;
    struct Unit_Block * unit_block;
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
    if (!(file = open_file(path)))
    {
        perror("file is not opened");
        free(serv);
        return (NULL);
    }
    unit_block = find_unit(file, unit);
//    print_unit(unit_block);
    if (!(serv->ip = find_ip(unit_block)))
    {
        perror("couldn't find ip");
        free(serv);
        return (NULL);
    }
    if(!(serv->user = find_user(unit_block)))
    {
        perror("cannot find user");
        return (NULL);
    }

    if(!(serv->password = find_password(unit_block)))
    {
        perror("cannot find password");
        return (NULL);
    }

    serv->port = find_port(unit_block);
    serv->family_type = find_family_type(unit_block);
    serv->sock_type = find_sock_type(unit_block);

    // free_unit_block !!!

    return serv;
}

int main(int argc, char **argv)
{
    struct Serv_Info * serv;

    if (argc != 3)
    {
        printf("missed conf and unit as arguments\n");
        return (1);
    }
    if (!(serv = parse_config(argv[1], argv[2])))
    {
        perror("parse failed");
        return (1);
    }
    printf("parse result is ip:%s| use:%s| password:%s| port:%d| family:%d| sock:%d|\n", serv->ip, serv->user, serv->password, serv->port, serv->family_type, serv->sock_type);
    /* connect serv will be call for Unix and AFINET differently */
// HAVE to check it and re do code, maybe as 1 function, in struct use pointer not type
// serv = connect_to_unix_serv(AF_UNIX, SOCK_STREAM, NULL, 54545);
    connect_to_serv(serv);
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
