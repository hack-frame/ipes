#include "ipesClient.h"


struct Server_Data * init_server(us_int ip_family, us_int socket_type, char * ip, int port)
{
        struct Server_Data * serv;

        if (ip_family > 12)
                fast_exit("ip family is not correct");
        if (!(socket_type >= 1 && socket_type <= 5) && socket_type != 10)
                fast_exit("socket type is not correct");
        /* IP string should have separate function to check values */
        if ((ip_family == AF_INET || ip_family == AF_INET6) && ip == NULL )
                fast_exit("ip is not correct");
        /* Use only these ports: 49152-65535 */
        if (port < 49152 || port > 65535)
                fast_exit("port is not correct");

        if (!(serv = (struct Server_Data *)malloc(sizeof(struct Server_Data))))
                fast_exit("malloc for serv failed");
        serv->serv_ip = ip;
        serv->serv_port = port;
        serv->msg = NULL;

        bzero(&serv->servaddr, sizeof(serv->servaddr));
        serv->servaddr.sin_family = ip_family;
        serv->servaddr.sin_port = htons(port);
printf("----------\n");
        if (serv->servaddr.sin_family == AF_INET || serv->servaddr.sin_family == AF_INET6)
                inet_pton(serv->servaddr.sin_family, serv->serv_ip, &serv->servaddr.sin_addr);

        return serv;
}

