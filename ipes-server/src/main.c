#include <stdio.h>

#include "ipes_serv_events.h"

int main()
{
    struct Server_Data * serv;
    printf("Hello World\n");
    //parse_conf()
    if (!(serv = init_serv(AF_INET, SOCK_STREAM, 54545)))
    {
        fprintf(stderr, "issue with init_server");
        return (1);
    }
    
    launch_serv(serv);
    //stop_server();
    fprintf(stderr, "we did it\n");
    return (0);
}
