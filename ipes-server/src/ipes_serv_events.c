#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipes_serv_events.h"

bool init_serv(struct Serv_Info * serv)
{
	if ((serv->sock_fd = socket(serv->family_type, serv->sock_type, 0)) == -1)
	{
		fprintf(stderr, "socket create failed\n");
		//free_serv;
		return (false);
	}

	bzero(&serv->servaddr, sizeof(serv->servaddr));
	serv->servaddr.sin_family = serv->family_type;
	serv->servaddr.sin_port = htons(serv->port);
	serv->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serv->sock_fd, (struct sockaddr *)&serv->servaddr, sizeof(serv->servaddr)) == -1)
	{
		fprintf(stderr, "issue bind\n");
//		free_serv !!!
		return false;
	}
	if (listen(serv->sock_fd, 2048) == -1)
	{
		fprintf(stderr, "issue listen\n");
//		free_serv !!!
		return false;
	}	

	return true;
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


