#include "ipes_server.hpp"

Server::Server()
{
    std::cout << "Server constructor is initializating empty" << std::endl;
}

Server::~Server()
{
    std::cout << "desctructor" << std::endl;
}

Server::Server(int port, int sock_type) :
        m_port(port), m_sock_type(sock_type)
{
    std::cout << "Server constructor: should add checing values" << std::endl;
}


bool Server::init_server()
{}

bool Server::launch_server()
{}

bool Server::close_server()
{}
