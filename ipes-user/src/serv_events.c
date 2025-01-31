#include "ipes_user.h"

bool connect_to_serv(struct Serv_Info * serv)
{
        if (!(serv->sock_type >= 1 && serv->sock_type <= 5) && serv->sock_type != 10)
                fast_exit("socket type is not correct");
        /* IP string should have separate function to check values */
        if (serv->family_type != AF_INET)
                fast_exit("ip is not correct");
        /* Use only these ports: 49152-65535 */
        if (serv->port < 49152 || serv->port > 65535)
                fast_exit("port is not correct");

        serv->msg = NULL;
        serv->sock_fd = socket(serv->family_type, serv->sock_type, 0);
        if (serv->sock_fd == -1)
        {
            perror("issue sockfd");
            free(serv);
            return false;
        }

        bzero(&serv->servaddr, sizeof(serv->servaddr));
        serv->servaddr.sin_family = serv->family_type;
        serv->servaddr.sin_port = htons(serv->port);
        inet_pton(serv->servaddr.sin_family, serv->ip, &serv->servaddr.sin_addr);

        return false;
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

