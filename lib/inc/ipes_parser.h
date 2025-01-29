#ifndef IPES_PARSER_H
#define IPES_PARSER_H

#include <stdio.h>
#include <stdint.h>

struct Unit_Block
{
    char * str;
    struct Unit_Block * next;
};

char * find_user(FILE * file, char * unit);
char * find_password(FILE * file, char * unit);
char * find_ip(FILE * file, char * unit);
char * find_sock_type(FILE * file, char * unit);
char * find_family_type(FILE * file, char * unit);
int find_serv_port(FILE * file, char * unit);
struct Unit_Block * find_unit(FILE * file, char * unit);
void print_unit(struct Unit_Block * unit_block);

#endif
