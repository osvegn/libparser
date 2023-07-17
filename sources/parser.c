#include "parser.h"

static parser_t parser = {0};

void init_parser()
{
    parser.options = NULL;
    parser.option_count = 0;
}

int add_option(char *short_name, char *long_name, char *key)
{
    if (!short_name || !key)
        return -1;
    parser.option_count++;
    if (parser.option_count == 1) {
        parser.options = malloc(sizeof(option_t));
        if (!parser.options)
            return -1;
        strncpy(parser.options[0].long_name, long_name, 256);
        strncpy(parser.options[0].short_name, short_name, 512);
        strncpy(parser.options[0].key, key, 256);
        parser.options[0].found = false;
    } else {
        parser.options = realloc(parser.options, sizeof(option_t) * parser.option_count);
        if (!parser.options)
            return -1;
        strncpy(parser.options[parser.option_count - 1].long_name, long_name, 256);
        strncpy(parser.options[parser.option_count - 1].short_name, short_name, 512);
        strncpy(parser.options[parser.option_count - 1].key, key, 256);
        parser.options[parser.option_count - 1].found = false;
    }
    return 0;
}

int parse_args(int ac, char **av)
{
    return 0;
}
