#include "parser.hpp"

Parser::Parser()
{
    m_port = 0;
    m_sock_type = 0;
    m_family_type = 0;
    std::cout << "constructor" << std::endl;
}

Parser::~Parser()
{
    std::cout << "destructor" << std::endl;
}

bool Parser::set_path(char * path)
{
    m_path = std::string(path);

    return (true);
}

bool Parser::set_unit(char * unit)
{
    m_unit = std::string(unit);

    return (true);
}

std::string Parser::get_path() const
{
    return (m_path);
}

std::string Parser::get_unit() const
{
   return (m_unit); 
}

int Parser::get_port() const
{
    return (m_port);
}

int Parser::get_family_type() const
{
    return (m_family_type);
}

int Parser::get_sock_type() const
{
    return (m_sock_type);
}


std::string Parser::get_ip() const
{
    return (m_ip);
}

std::string Parser::get_user() const
{
    return (m_user);
}

std::string Parser::get_password() const
{
    return (m_password);
}

bool Parser::parse_conf()
{
    struct Unit_Block * unit;
    FILE * file_fd;

    if (m_path.empty() || m_unit.empty())
    {
        std::cout << "path or unit is not set" << std::endl;
        return (false);
    }
    if (!(file_fd = open_file(const_cast<char*>(m_path.c_str()))))
    {
        std::cout << "couldn't open file" << std::endl;
        return (false);
    }

    if (!(unit = find_unit(file_fd, const_cast<char*>(m_unit.c_str()))))
    {
        std::cout << "couldn't find unit" << std::endl;
        delete unit;
        return (false);
    }
    print_unit(unit);
    if (!(m_port = find_port(unit)))
    {
        std::cout << "couldn't find port" << std::endl;
        delete unit;
        return (false);
    }
    if (!(m_family_type = find_family_type(unit)))
    {
        std::cout << "couldn't find family type" << std::endl;
        delete unit;
        return (false);
    }

    delete unit;

    return true;

}