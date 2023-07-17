#include "parser.h"
#include <stdlib.h>
#include <string.h>

static parser_t parser = {0};

void init_parser(void)
{
    parser.options = 0;
    parser.option_count = 0;
}

parser_t *get_parser(void)
{
    return &parser;
}

void del_parser(void)
{
    if (parser.options)
        free(parser.options);
}


int add_option(char *short_name, char *long_name, char *key)
{
    if (!long_name || !key)
        return -1;
    parser.options = realloc(parser.options, sizeof(option_t) * (parser.option_count + 1));
    if (!parser.options)
        return -1;
    strncpy(parser.options[parser.option_count].long_name, long_name, 512);
    if (short_name)
        strncpy(parser.options[parser.option_count].short_name, short_name, 256);
    else
        memset(parser.options[0].short_name, 0, 256);
    strncpy(parser.options[parser.option_count].key, key, 256);
    parser.options[parser.option_count].found = false;
    parser.option_count++;
    return 0;
}

static bool is_in(char *str, char **table, int table_size)
{
    for (int i = 0; i < table_size && table[i]; i++) {
        if (strcmp(str, table[i]) == 0)
            return true;
    }
    return false;
}

int parse_args(int ac, char **av)
{
    for (int j = 0; j < parser.option_count; j++) {
        if ((parser.options[j].short_name[0] && is_in(parser.options[j].short_name, av + 1, ac - 1)) || is_in(parser.options[j].long_name, av + 1, ac - 1)) {
            parser.options[j].found = true;
            if (j + 1 < parser.option_count && !is_in(parser.options[j].short_name, av + 1, ac - 1) && !is_in(parser.options[j].long_name, av + 1, ac - 1)) {
                strncpy(parser.options[j].value, av[j + 1], 512);
            }
        }
    }
    return 0;
}
