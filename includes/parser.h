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

/**
 * @author osvegn
 * @name init_parser
 * @brief Parser initializer. Must be used at the beginning to
 * setup the parser.
*/
void init_parser(void);

/**
 * @author osvegn
 * @name get_parser
 * @brief Getter which returns the instance of the parser.
 * @return const parser_t pointer.
*/
parser_t *get_parser(void);

/**
 * @author osvegn
 * @name del_parser
 * @brief Parser destructor. Must be used at the end to delete
 * the parser.
*/
void del_parser(void);

/**
 * @author osvegn
 * @name parse_args
 * @brief Argument parser. It fills defined options with
 * corresponding values.
 * @param ac int | Number of arguments.
 * @param av array of string | Arguments.
 * @return int | 0
*/
int parse_args(int ac, const char **av);

/**
 * @author osvegn
 * @name add_option
 * @brief Configure new option. It defines new available option to parser.
 * @param short_name str | Short name of the option (256).
 * (example: "-v")
 * @param long_name str | Long name of the option (512).
 * (example: "--version")
 * @param key str | Key of the option (256). (example: "version")
 * @param help str | Help message to print on help (1024).
 * (example: "Print version")
 * @return int | -1 if long_name or key is null, or if realloc failed.
 * 0 on success.
*/
int add_option(char *short_name, char *long_name, char *key, char *help);

/**
 * @author osvegn
 * @name get_value
 * @brief Get value from key.
 * @param key str | Key to get value from.
 * @return str | Value of the key.
 * 0 if key not found or if option isn't filled.
*/
char *get_value(char *key);

/**
 * @author osvegn
 * @name dump
 * @brief Dump parser. It display in a human readable way the stat of
 * the parser.
*/
void dump(void);
