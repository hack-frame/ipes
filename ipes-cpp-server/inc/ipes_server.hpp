#pragma once

#include <iostream>
#include <string>

/* !!! NETWORK LIBS !!! */
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define BUFF_SIZE 1024

class Server
{
private:
    int m_sock_fd;
    int m_port;
    int m_family_type;
    int m_sock_type;
    struct sockaddr_in m_servaddr;
    char m_buff[BUFF_SIZE];

public:
    Server();
    Server(int port, int sock_type);
    ~Server();
    bool init_server(int port, int sock_type, int family_type);
    bool launch_server();
    bool close_server();
    
};