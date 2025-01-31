#ifndef IPES_PARSER_H
#define IPES_PARSER_H

#include <stdio.h>
#include <stdint.h>

#include "ipes_defenitions.h"

struct Unit_Block
{
    char * str;
    struct Unit_Block * next;
};

/* mandatory fields */
char * find_ip(struct Unit_Block * unit);
char * find_user(struct Unit_Block * unit);
char * find_password(struct Unit_Block * unit);

int find_sock_type(struct Unit_Block * unit);
int find_family_type(struct Unit_Block * unit);
int find_port(struct Unit_Block * unit);
struct Unit_Block * find_unit(FILE * file, char * unit);
bool print_unit(struct Unit_Block * unit_block);

#endif
