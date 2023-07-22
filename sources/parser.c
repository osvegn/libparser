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


int add_option(char *short_name, char *long_name, char *key, char *help)
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
    if (help)
        strncpy(parser.options[parser.option_count].help, help, 1024);
    else
        memset(parser.options[0].help, 0, 1024);
    strncpy(parser.options[parser.option_count].key, key, 256);
    parser.options[parser.option_count].found = false;
    parser.option_count++;
    return 0;
}

static bool is_in_parser(char *str, int *index)
{
    for ((*index) = 0; (*index) < parser.option_count; (*index)++) {
        if (strncmp(str, parser.options[(*index)].short_name, 256) == 0)
            return true;
        if (strncmp(str, parser.options[(*index)].long_name, 512) == 0)
            return true;
    }
    (*index) = 0;
    return false;
}

int parse_args(int ac, char **av)
{
    int option_index = 0;

    for (int i = 1; i < ac; i++) {
        if (is_in_parser(av[i], &option_index)) {
            parser.options[option_index].found = true;
            if (i + 1 < ac && !is_in_parser(av[i + 1], &option_index))
                strncpy(parser.options[option_index].value, av[i + 1], 512);
        }
    }
    return 0;
}
