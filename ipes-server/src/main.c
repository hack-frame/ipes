#include <stdio.h>
#include <stdlib.h>

#include "ipes_serv_events.h"
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
    if (!(file = fopen(path, "r")))
    {
        perror("cannot open file");
        free(serv);
        return (NULL);
    }
    unit_block = find_unit(file, unit);
    print_unit(unit_block);

    serv->port = find_port(unit_block);
    serv->family_type = find_family_type(unit_block);
    serv->sock_type = find_sock_type(unit_block);
    printf("|%d|%d|%d\n",serv->port, serv->family_type, serv->sock_type);

    return serv;
}

int main(int argc, char ** argv)
{
    struct Serv_Info * serv;
    //parse_conf()
    //

    if (argc != 3)
    {
        printf("missed conf and unit as arguments\n");
        return (1);
    }
    serv = parse_config(argv[1], argv[2]);
    if (!init_serv(serv))
    {
        fprintf(stderr, "issue with init_server");
        return (1);
    }
    
    launch_serv(serv);
    //stop_server();
    fprintf(stderr, "we did it\n");
    return (0);
}
