#include <stdlib.h>
#include <string.h>

#include "ipes_parser.h"
#include "ipes_defenitions.h"

void print_unit(struct Unit_Block  * unit_block)
{
    struct Unit_Block * tmp_unit;
    tmp_unit = unit_block;
    while(tmp_unit->next != NULL)
    {
        printf("| %s\n", unit_block->str);
        tmp_unit = tmp_unit->next;
    }

}

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
    while(fgets(line, sizeof(line),file))
        if (strcmp(line, unit))
            is_find++;
    if (is_find == 0)
    {
        perror("didn't find unit");
//        free_unit_block();
        return (NULL);
    }
    rewind(file);
    while (fgets(line, sizeof(line), file))
    {
        if (strcmp(line, unit))
            i++;
        if (line[0] == '[')
            break;
        if (i == is_find)
        {
            if (strlen(line) == 0)
                continue;
            if (!(unit_block->str = (char *)malloc(sizeof(char) * strlen(line))))
            {
                perror("malloc failed for str in unit_block");
//                free_unit_block();
                return (NULL);
            }
            strcpy(unit_block->str, line);
            /* Create next Unit_Block with NULL field and move to it*/
            if (!(unit_block->next = (struct Unit_Block *)malloc(sizeof(struct Unit_Block))))
            {
                perror("failed allocate mem init_block->next");
//              free_unit_block();
                return (NULL);
            }
            unit_block = unit_block->next;
            unit_block->next = NULL;
            unit_block->str = NULL;
        } 
    }

    return (unit_tmp);
}
