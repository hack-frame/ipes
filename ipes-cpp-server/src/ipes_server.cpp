#include "ipes_server.hpp"

Server::Server()
{
    m_sock_fd = 0;
    m_port = 0;
    m_family_type = 0;
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


bool Server::init_server(int port, int sock_type, int family_type)
{
    m_port = port;
    m_sock_type = sock_type;
    m_family_type = family_type;

    if (!(m_sock_fd = socket(m_family_type, m_sock_type, 0)))
    {
        std::cout << "socket for serv didn't created" << std::endl;
        return (false);
    }
    
    bzero(&m_servaddr, sizeof(m_servaddr));
    m_servaddr.sin_family = m_family_type;
    m_servaddr.sin_port = htons(m_port);
    m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(m_sock_fd, (struct sockaddr *)&m_servaddr, sizeof(m_servaddr)) == -1)
    {
        std::cout << "bind issue" << std::endl;
        return (false);
    }
    if (listen(m_sock_fd, 2048) == -1)
    {
        std::cout << "listen issue" << std::endl;
        return (false);
    }

    return (true);
}

bool Server::launch_server()
{
	int connfd;
 
	while (1)
	{
		if ((connfd = accept(m_sock_fd, NULL, NULL)) == -1)
		{
			printf("issue accept\n");
			return false;
		}
		bzero(&m_buff, BUFF_SIZE - 1);
		recv(connfd, m_buff, BUFF_SIZE - 1, 0);
		printf("GOT: %s\n", m_buff);
		bzero(&m_buff, BUFF_SIZE);
		strcpy(m_buff, "GOT IT\n");
		send(connfd, m_buff, BUFF_SIZE - 1, 0);
		close(connfd);
	}

    return (true);
}

bool Server::close_server()
{}
