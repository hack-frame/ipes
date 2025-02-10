#pragma once

#include <iostream>

#include "ipes_parser.h"

class Parser
{
private:
    int m_port;
    int m_sock_type;
    int m_family_type;
    std::string m_ip;
    std::string m_user;
    std::string m_password;
    std::string m_path;
    std::string m_unit;

public:
    Parser();
    ~Parser();
    bool set_path(char * path);
    bool set_unit(char * unit);
    int get_port() const;
    int get_family_type() const;
    std::string get_path() const;
    std::string get_unit() const;

    /* stubs */
    int get_sock_type() const;
    std::string get_ip() const;
    std::string get_user() const;
    std::string get_password() const;

    bool parse_conf();

};
