#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ipes_parser.h"
#include "ipes_defenitions.h"

bool free_unit_block(struct Unit_Block * unit)
{
    struct Unit_Block * tmp_unit;
    while (unit)
    {
        tmp_unit = unit->next;
        if (unit->str)
            free(unit->str);
        if (unit)
            free(unit);
        unit = tmp_unit;
    }

    return (true);
}


bool print_unit(struct Unit_Block  * unit)
{
    struct Unit_Block * tmp_unit;
    tmp_unit = unit;

    if (unit == NULL)
        return (false);
    while(tmp_unit != NULL)
    {
        if (tmp_unit->str != NULL)
            printf("|%p - %s\n", tmp_unit, tmp_unit->str);
        tmp_unit = tmp_unit->next;
    }
    return (true);
}

/* this function with leaks in both good and bad case */
struct Unit_Block * find_unit(FILE * file, char * unit)
{
    struct Unit_Block * unit_block;
    struct Unit_Block * unit_tmp;
    char line[256];
    int i;
    bool is_find;

    is_find = 0;
    i = 0;

    if (!(unit_block = (struct Unit_Block *)malloc(sizeof(struct Unit_Block))))
    {
        perror("failed malloc mem in find_unit");
        return (NULL);
    }
    unit_block->next = NULL;
    unit_tmp = unit_block;
    /*looking for last enterance unit name. If couldn't find return NULL */
    while(fgets(line, sizeof(line),file))
    {
        /* tream line as strcmp will not work */
        if (strlen(line) > 0  && line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (strcmp(line, unit) == 0)
        {
            is_find++;
        }
    }
    if (is_find == 0)
    {
        perror("didn't find unit");
        free_unit_block(unit_tmp);
        return (NULL);
    }
    rewind(file);
    /* move to last enterance of unit and save fields */
    while (fgets(line, sizeof(line), file))
    {
        /* tream line as strcmp will not work */
        if (strlen(line) > 0  && line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (strcmp(line, unit) == 0)
        {
            i++;
            if (i == is_find)
                continue;
        }
        if (i == is_find)
        {
            if (line[0] == '[')
                break;
            if (strlen(line) == 0)
                continue;
            if (!(unit_block->str = (char *)malloc(sizeof(char) * strlen(line))))
            {
                perror("malloc failed for str in unit_block");
                free_unit_block(unit_tmp);
                return (NULL);
            }
            strcpy(unit_block->str, line);
            /* Create next Unit_Block with NULL field and move to it. Last block always will have NULLS*/
            if (!(unit_block->next = (struct Unit_Block *)malloc(sizeof(struct Unit_Block))))
            {
                perror("failed allocate mem init_block->next");
                free_unit_block(unit_tmp);
                return (NULL);
            }
            unit_block = unit_block->next;
            unit_block->next = NULL;
            unit_block->str = NULL;
        } 
    }

    return (unit_tmp);
}

char * substr(char * str, int pos, int len)
{
    char * substr;
    int str_len;

    if (str == NULL)
        return (NULL);
    str_len = strlen(str);
    if (str_len < pos + len)
        return (NULL);
    if (!(substr = (char *)malloc(sizeof(char) * len)))
    {
        perror("malloc failed in substr");
        return (NULL);
    }
    for (int i = 0; i < len; i++)
        substr[i] = str[i + pos];

    return substr;
}

static char * mining_char_value(char * line, char * option)
{
    char * value_str;
    char * sub_str;
    bool is_eq;
    bool get_value;

    sub_str = NULL;
    is_eq = false;
    value_str = NULL;
    get_value = false;

    /* check is line ok */
    if (strlen(line) > strlen(option))
    {
        sub_str = substr(line, 0, strlen(option));
        /* if option is not present return NULL */
        if (strcmp(sub_str, option) == 0)
        {
            free(sub_str);
            /* devide sub_str anf get value, first remove "option =", 
            then comments which started after #,
            then remove spaces and left only value */
            sub_str = substr(line, strlen(option), strlen(line) - strlen(option));
            for (size_t i = 0; i < strlen(sub_str); i++)
            {
                if (sub_str[i] == ' ')
                    continue;
                if (sub_str[i] == '=' && is_eq == false)
                {
                    is_eq = true;
                    continue;
                }
                if (sub_str[i] == '=' && is_eq == true)
                {
                    fprintf(stderr, "bad conf file. = is bad located.");
                    break;
                }
                if (get_value == false)
                {
                    /* get len of value, then use that index and copy */
                    size_t j;
                    for (j = i; j < strlen(sub_str) || sub_str[j] == ' ' || sub_str == NULL; j++)
                        ;
                    value_str = substr(sub_str,i, j - i);
                    get_value = true;
                    i = j;
                }
                else
                {
                   fprintf(stderr, "bad line %s", line);
                   break; 
                }
            }

        }
        free(sub_str);
    }
    

    return (value_str);
}

static char * get_value_by_option(struct Unit_Block * unit, char * option)
{
    char * str;

    while (unit != NULL)
    {
        if (unit->str != NULL)
        {
            if ((str = mining_char_value(unit->str, option)) == NULL)
            {
                unit = unit->next;
                continue;
            }
            else
                break;
        }
        unit = unit->next;
    }
    return (str);
}

static char * create_str(char * src)
{
    char * str;
    size_t len;

    len = strlen(src);
    if (!(str = (char *)malloc(sizeof(char) * len)))
    {
        fprintf(stderr, "malloc failed create_str()\n");
        return NULL;
    } 
    for (size_t i = 0; i < len; i++)
        str[i] = src[i];

    str[len] = '\0';

    return str;
}

char * find_ip(struct Unit_Block * unit)
{
    char * value;

    value = get_value_by_option(unit, "server_ip");

    /* Should check value? */
    /* if not remove all functions as find_ip find_user and call get_value_by_option directly*/

    return (value);

}


char * find_user(struct Unit_Block * unit)
{
    char *value;

    value = get_value_by_option(unit, "user");

    return (value);
}


char * find_password(struct Unit_Block * unit)
{
    char * value;

    value = get_value_by_option(unit, "password");

    return (value);
}

int find_sock_type(struct Unit_Block * unit)
{
    int ret;
    char * value;

    ret = 0;
    if ((value = get_value_by_option(unit, "SOCK_STREAM")) == NULL)
        value = create_str("SOCK_STREAM");

    if (!strcmp(value, "SOCK_STREAM"))
        ret = 1;
    else
        fprintf(stderr, "!!!!! soc type is not full !!!!!");

    free(value);

    return (ret);
}

int find_family_type(struct Unit_Block * unit)
{
    int ret;
    char * value;

    ret = 0;
    if ((value = get_value_by_option(unit, "AF_INET")) == NULL)
        value = create_str("AF_INET");

    if (!strcmp("AF_INET", value))
        ret = 2;
    else
        fprintf(stderr, "!!!!! family type is not full !!!!!");

    free(value);
    return (ret);
}


int find_port(struct Unit_Block * unit)
{
    char * value;
    int ret;

    ret  = 0;
    if ((value = get_value_by_option(unit, "server_port")) == NULL)
        ret = DEFAULT_PORT;
    else
        ret = atoi(value);

    free(value);

    return ret;
}

FILE * open_file(char * path)
{
    FILE * fd;

    if (!(fd = fopen(path, "r")))
    {
        perror("cannot open file");
        return (0);
    }

    return (fd);
}
