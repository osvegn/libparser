/*
 * Filename: sources/parser.c
 * Path: sources
 * Created Date: Friday, August 4th 2023, 1:28:12 pm
 * Author: osvegn
 * 
 * Copyright (c) 2023 Your Company
 */


#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static parser_t parser = {0};

void init_parser(void)
{
    parser.options = 0;
    parser.option_count = 0;
    add_option("-h", "--help", "help", "Show help");
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
        memset(parser.options[parser.option_count].short_name, 0, 256);
    if (help)
        strncpy(parser.options[parser.option_count].help, help, 1024);
    else
        memset(parser.options[parser.option_count].help, 0, 1024);
    strncpy(parser.options[parser.option_count].key, key, 256);
    parser.options[parser.option_count].found = false;
    memset(parser.options[parser.option_count].value, 0, 512);
    parser.option_count++;
    return 0;
}

static bool is_in_parser(char *str, int *index)
{
    int len = 0;

    for ((*index) = 0; (*index) < parser.option_count; (*index)++) {
        len = strlen(parser.options[(*index)].short_name);
        if (strncmp(str, parser.options[(*index)].short_name, len) == 0)
            return true;
        len = strlen(parser.options[(*index)].long_name);
        if (strncmp(str, parser.options[(*index)].long_name, len) == 0)
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
            int tmp = option_index;
            if (i + 1 < ac && !is_in_parser(av[i + 1], &tmp))
                strncpy(parser.options[option_index].value, av[i + 1], 512);
            if (av[i][strlen(parser.options[option_index].long_name)] == '=')
                strncpy(parser.options[option_index].value, av[i] + strlen(parser.options[option_index].long_name) + 1, 512);
        }
    }
    return 0;
}

static int index_from_key(char *key)
{
    int i = 0;

    if (!key)
        return -1;
    for (; i < parser.option_count; i++) {
        if (strcmp(parser.options[i].key, key) == 0)
            return i;
    }
    return -1;
}

char *get_value(char *key)
{
    int index = index_from_key(key);

    if (index < 0)
        return 0;
    if (!parser.options[index].found)
        return 0;
    return parser.options[index].value;
}

void dump(void)
{
    int i = 0;
    option_t *option = 0;

    printf("----------\n");
    while (parser.option_count > i) {
        option = &parser.options[i];
        printf("option_number:\t%d\nshort_name:\t%s\nlong_name:\t%s\nkey:\t\t%s\nvalue:\t\t%s\nhelp:\t\t%s\nfound:\t\t%s\n\n", i, option->short_name, option->long_name, option->key, option->value, option->help, (option->found) ? "True" : "False");
        i++;
    }
    printf("----------\n");
    fflush(stdout);
}
