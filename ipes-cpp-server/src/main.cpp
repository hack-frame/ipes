#include <iostream>

#include "parser.hpp"
#include "ipes_server.hpp"

int main(int argc, char **argv)
{
    Parser *parser;
    Server *server;

    if (argc != 3)
    {
        std::cout << "provide incorrect argc" << std::endl;
       return (0);
    }
    parser = new Parser();
    parser->set_path(argv[1]);
    parser->set_unit(argv[2]);
    std::cout << "path: " << parser->get_path() << " unit: " << parser->get_unit() << std::endl;
    if (!parser->parse_conf())
    {
        delete parser;
        return (0);
    }
    std::cout << "port: " << parser->get_port() << " family: " << parser->get_family_type() << std::endl;

    server = new Server();
    if (!server->init_server(parser->get_port(), parser->get_sock_type(), parser->get_family_type()))
    {
        delete parser;
        delete server;
        return (0);
    }
    server->launch_server();
//    server.stop_serv;
//    delete parser;
//    delete server;

    delete parser;
    delete server;
    return (0);
}
