#include "ipes_user.h"

#define SERVER_IP "192.168.0.108"

struct Serv_Info * connect_to_serv(char ip_family, char socket_type, char * ip, int port)
{
        struct Serv_Info * serv;

        if (!(socket_type >= 1 && socket_type <= 5) && socket_type != 10)
                fast_exit("socket type is not correct");
        /* IP string should have separate function to check values */
        if (ip_family != AF_INET)
                fast_exit("ip is not correct");
        /* Use only these ports: 49152-65535 */
        if (port < 49152 || port > 65535)
                fast_exit("port is not correct");

        if (!(serv = (struct Serv_Info *)malloc(sizeof(struct Serv_Info))))
        {
            perror("serv malloc failed");
            return NULL;
        }

        serv->msg = NULL;
        serv->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (serv->sock_fd == -1)
        {
            perror("issue sockfd");
            free(serv);
            return NULL;
        }

        bzero(&serv->servaddr, sizeof(serv->servaddr));
        serv->servaddr.sin_family = ip_family;
        serv->servaddr.sin_port = htons(port);
        inet_pton(serv->servaddr.sin_family, SERVER_IP, &serv->servaddr.sin_addr);

        return serv;
}

bool send_to_serv(struct Serv_Info * serv, struct Ipes_msg * msg)
{
   if((connect(serv->sock_fd, (struct sockaddr *)&serv->servaddr, sizeof(serv->servaddr)) == -1))
    {
        perror("failed connect to server");
        free(serv);
        return false;
    }

    printf("input val:\n");
    scanf("%s", serv->buff);
    send(serv->sock_fd, serv->buff, strlen(serv->buff), 0);
    bzero(&serv->buff, BUFF_SIZE);
    recv(serv->sock_fd, serv->buff, BUFF_SIZE -1, 0);
    printf("got: %s", serv->buff);
    close(serv->sock_fd);

    return true;
}

