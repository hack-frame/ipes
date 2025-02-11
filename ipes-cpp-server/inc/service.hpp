#pragma once

#include <iostream>
#include <string>

class Service
{
private:
    char id;
    char log_lvl;
    short int port;
    std::string ip;
    std::string name;
public:
    Service();
    Service(short int port, std::string ip, std::string name, char id);
    ~Service();
    Service &operator=(Service const &src);
    
    char get_id() const;
    char get_log_lvl() const;
    short int get_port() const;
    std::string get_ip() const;
    std::string get_name() const;
};
