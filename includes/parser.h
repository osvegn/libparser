/*
 * Filename: includes/parser.h
 * Path: includes
 * Created Date: Friday, August 4th 2023, 1:28:12 pm
 * Author: osvegn
 * 
 * Copyright (c) 2023 Your Company
 */


#include <stdbool.h>

typedef struct option_s {
    char short_name[256];
    char long_name[512];
    char key[256];
    char value[512];
    char help[1024];
    bool found;
} option_t;

typedef struct parser_s {
    option_t *options;
    int option_count;
} parser_t;

void init_parser(void);
parser_t *get_parser(void);
void del_parser(void);

int parse_args(int ac, char **av);
int add_option(char *short_name, char *long_name, char *key, char *help);
char *get_value(char *key);
void dump(void);
