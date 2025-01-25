#include <stdio.h>

#include "ipesServer.h"

int main()
{
	printf("Hello World\n");
	//parse_conf()
	init_server();
	launch_server();
	//stop_server();
	return (0);
}
