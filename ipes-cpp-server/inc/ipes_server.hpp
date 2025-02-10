#pragma once

#include <iostream>
#include <string>

class Server
{
private:
    int m_fd;
    int m_port;
    int m_sock_type;
    int m_family_type;

public:
    Server();
    Server(int port, int sock_type);
    ~Server();
    bool init_server();
    bool launch_server();
    bool close_server();
    
};