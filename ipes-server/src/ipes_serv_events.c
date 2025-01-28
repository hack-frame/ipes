#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipes_serv_events.h"

struct Serv_Info * init_serv(uint8_t ip_family, uint8_t socket_type, int port)
{
	struct Serv_Info * serv;

	if (!(serv = (struct Serv_Info *)malloc(sizeof(struct Serv_Info))))
	{
		fprintf(stderr, "malloc didn't allocated memmory for serv\n");
		return NULL;
	}

	serv->serv_port = port;
	serv->sock_fd = 0;

	if ((serv->sock_fd = socket(ip_family, socket_type, 0)) == -1)
	{
		fprintf(stderr, "socket create failed\n");
		free(serv);
		return (NULL);
	}

	bzero(&serv->servaddr, sizeof(serv->servaddr));
	serv->servaddr.sin_family = ip_family;
	serv->servaddr.sin_port = htons(serv->serv_port);
	serv->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serv->sock_fd, (struct sockaddr *)&serv->servaddr, sizeof(serv->servaddr)) == -1)
	{
		fprintf(stderr, "issue bind\n");
		free(serv);
		return NULL;
	}
	if (listen(serv->sock_fd, 2048) == -1)
	{
		fprintf(stderr, "issue listen\n");
		free(serv);
		return NULL;
	}	

	return serv;
}

bool launch_serv(struct Serv_Info * serv)
{
	int connfd;
 
	while (1)
	{
		if ((connfd = accept(serv->sock_fd, NULL, NULL)) == -1)
		{
			printf("issue accept\n");
			return false;
		}
		bzero(&serv->buff, BUFF_SIZE -1);
		recv(connfd, serv->buff, BUFF_SIZE - 1, 0);
		printf("GOT: %s\n", serv->buff);
		bzero(&serv->buff, BUFF_SIZE);
		strcpy(serv->buff, "GOT IT\n");
		send(connfd, serv->buff, BUFF_SIZE - 1, 0);
		close(connfd);
	}

	return true;
}


