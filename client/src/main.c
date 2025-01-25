#include <stdio.h>
#include <ipesClient.h>

void fast_exit(char * msg)
{
	printf("%s\n", msg);
	exit(1);
}

int main(int argc, char **argv)
{
	struct Server_Data * serv;
	if (argc != 1)
	{
		printf("parsing is not support right now\n");
		return (1);
	}

serv = init_server(AF_UNIX, SOCK_STREAM, NULL, 54545);
/*	init_msg();
	connect_to_server();
	send_to_server();
	close_server_conn();*/
    printf("We did it\n");
    return (0);
}
