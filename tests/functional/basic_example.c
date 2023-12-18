/*
 * Filename: basic_example.c
 * Path: tests/functional
 * Created Date: Monday, July 17th 2023, 8:07:36 pm
 * Author: osvegn
 *
 * Copyright (c) 2023 libparser
 */

#include "parser.h"
#include <stdio.h>

void print_help(void)
{
    printf("Usage: ./basic_example [OPTION]...\n");
    printf("Options:\n");
    printf("  -h, --help\t\t\tPrint this help message\n");
    printf("  -v, --version\t\t\tPrint the version\n");
    printf("  -q, --quit\t\t\tQuit the program\n");
}

int main(int argc, char **argv)
{
    init_parser();
    add_option("-v", "--version", "version", "");
    add_option("-q", "--quit", "quit", "");
    parse_args(argc, argv);
    if (is_option_found("help"))
        print_help();
    if (is_option_found("version"))
        printf("Version 1.0.0\n");
    if (is_option_found("quit"))
        printf("Bye!\n");
    del_parser();
    return 0;
}
