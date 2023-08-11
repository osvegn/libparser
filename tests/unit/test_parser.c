/*
 * Filename: tests/unit/test_parser.c
 * Path: tests/unit
 * Created Date: Monday, July 17th 2023, 8:07:36 pm
 * Author: osvegn
 * 
 * Copyright (c) 2023 Your Company
 */


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "parser.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init_parser, create_empty_parser)
{
    init_parser();
    cr_assert_neq(get_parser(), 0);
    del_parser();
}

Test(init_parser, create_one_option_parser)
{
    init_parser();
    cr_assert_eq(add_option("-v", "--version", "version", ""), 0);
    cr_assert_eq(get_parser()->option_count, 2);
    del_parser();
}

Test(init_parser, create_two_options_parser)
{
    init_parser();
    cr_assert_eq(add_option("-v", "--version", "version", ""), 0);
    cr_assert_eq(add_option("-q", "--quit", "quit", ""), 0);
    cr_assert_eq(get_parser()->option_count, 3);
    del_parser();
}

Test(init_parser, create_parser_null_short_name)
{
    init_parser();
    cr_assert_eq(add_option(0, "--version", "version", ""), 0);
    cr_assert_eq(get_parser()->option_count, 2);
    del_parser();
}

Test(init_parser, create_parser_null_long_name)
{
    init_parser();
    cr_assert_eq(add_option("-v", 0, "version", ""), -1);
    cr_assert_eq(get_parser()->option_count, 1);
    del_parser();
}

Test(init_parser, create_parser_null_key)
{
    init_parser();
    cr_assert_eq(add_option("-v", "--version", 0, ""), -1);
    del_parser();
}

Test(parse_args, parser_one_arg_one_option)
{
    const char *args[] = {"test", "--version"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    parse_args(2, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    del_parser();
}

Test(parse_args, parser_one_arg_two_options)
{
    const char *args[] = {"test", "--quit"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    if (add_option("-q", "--quit", "quit", "") < 0)
        return;
    parse_args(2, args);
    cr_assert_eq(get_parser()->options[1].found, false);
    cr_assert_eq(get_parser()->options[2].found, true);
    del_parser();
}

Test(parse_args, parser_one_arg_one_option_with_value)
{
    const char *args[] = {"test", "--version", "vers"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    if (add_option("-q", "--quit", "quit", "") < 0)
        return;
    parse_args(3, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    cr_assert_eq(strcmp(get_parser()->options[1].value, "vers"), 0);
    cr_assert_eq(get_parser()->options[2].found, false);
    del_parser();
}

Test(parse_args, create_parser_null_help)
{
    const char *args[] = {"test", "--version", "vers"};

    init_parser();
    if (add_option("-v", "--version", "version", NULL) < 0)
        return;
    parse_args(3, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    del_parser();
}

Test(parse_args, parser_one_arg_one_option_with_value_and_short_option)
{
    const char *args[] = {"test", "-v", "vers"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    if (add_option("-q", "--quit", "quit", "") < 0)
        return;
    parse_args(3, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    cr_assert_eq(strcmp(get_parser()->options[1].value, "vers"), 0);
    cr_assert_eq(get_parser()->options[2].found, false);
    del_parser();
}

Test(parse_args, parser_one_arg_one_option_with_value_using_equal)
{
    const char *args[] = {"test", "--version=salut"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    parse_args(2, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    cr_assert_eq(strcmp(get_parser()->options[1].value, "salut"), 0);
    del_parser();
}

Test(parse_args, parser_multi_args_multi_options)
{
    const char *args[] = {"test", "--load", "-v", "--help", "coucou", "--test"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    if (add_option("-l", "--load", "load", "") < 0)
        return;
    if (add_option("-t", "--test", "test", "") < 0)
        return;
    if (add_option("-r", "--recursive", "recursive", "") < 0)
        return;
    if (add_option("-lt", "--less-than", "less-than", "") < 0)
        return;
    parse_args(6, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    cr_assert_eq(strcmp(get_parser()->options[1].value, "\0"), 0);
    cr_assert_eq(get_parser()->options[2].found, true);
    cr_assert_eq(strcmp(get_parser()->options[2].value, ""), 0);
    cr_assert_eq(get_parser()->options[3].found, true);
    cr_assert_eq(strcmp(get_parser()->options[3].value, ""), 0);
    cr_assert_eq(get_parser()->options[4].found, false);
    cr_assert_eq(strcmp(get_parser()->options[4].value, ""), 0);
    cr_assert_eq(get_parser()->options[5].found, false);
    cr_assert_eq(strcmp(get_parser()->options[5].value, ""), 0);
    del_parser();
}

Test(get_value, test_get_value)
{
    const char *args[] = {"test", "--load", "-v", "--help", "coucou", "--test"};

    init_parser();
    add_option("-v", "--version", "version", "");
    parse_args(6, args);
    cr_assert_neq(get_value("version"), 0);
    del_parser();
}

Test(get_value, test_get_value_null_key)
{
    cr_assert_eq(get_value(NULL), 0);
}

Test(get_value, test_get_value_null_key_init_parser)
{
    const char *args[] = {"test", "--load", "-v", "--help", "coucou", "--test"};

    init_parser();
    add_option("-v", "--version", "version", "");
    parse_args(6, args);
    cr_assert_eq(get_value(NULL), 0);
    del_parser();
}

Test(get_value, test_get_value_empty_key_init_parser)
{
    const char *args[] = {"test", "--load", "-v", "--help", "coucou", "--test"};

    init_parser();
    add_option("-v", "--version", "version", "");
    parse_args(6, args);
    cr_assert_eq(get_value(""), 0);
    del_parser();
}

Test(get_value, test_get_value_not_found_key)
{
    const char *args[] = {"test", "--load", "-r", "--help", "coucou", "--test"};

    init_parser();
    add_option("-v", "--version", "version", "");
    parse_args(6, args);
    cr_assert_eq(get_value("version"), 0);
    del_parser();
}

Test(dump, test_dump_parser, .init = redirect_all_stdout)
{
    const char *args[] = {"test", "--version"};
    char output[2048];

    memset(output, 0, 2048);
    strcpy(output, "----------\n");
    strcat(output, "option_number:\t0\n");
    strcat(output, "short_name:\t-h\n");
    strcat(output, "long_name:\t--help\n");
    strcat(output, "key:\t\thelp\n");
    strcat(output, "value:\t\t\n");
    strcat(output, "help:\t\tShow help\n");
    strcat(output, "found:\t\tFalse\n\n");
    strcat(output, "option_number:\t1\n");
    strcat(output, "short_name:\t-v\n");
    strcat(output, "long_name:\t--version\n");
    strcat(output, "key:\t\tversion\n");
    strcat(output, "value:\t\t\n");
    strcat(output, "help:\t\t\n");
    strcat(output, "found:\t\tTrue\n\n");
    strcat(output, "----------\n");
    init_parser();
    add_option("-v", "--version", "version", "");
    parse_args(2, args);
    dump();
    cr_assert_stdout_eq_str(output);
    del_parser();
}

Test(dump, test_empty_dump, .init=redirect_all_stdout)
{
    dump();
    cr_assert_stdout_eq_str("----------\n----------\n");
}

Test(is_option_found, test_is_option_found)
{
    const char *args[] = {"test", "-v"};

    init_parser();
    if (add_option("-v", "--version", "version", "version") < 0)
        cr_assert_eq(1, 0);
    if (add_option("-r", "--recursive", "recursive", "recursive") < 0)
        cr_assert_eq(1, 0);
    parse_args(2, args);
    cr_assert_eq(is_option_found("version"), true);
    cr_assert_eq(is_option_found("recursive"), false);
    del_parser();
}

Test(is_option_found, test_is_option_found_no_parser)
{
    cr_assert_eq(is_option_found("version"), false);
}

Test(is_option_found, test_is_option_found_invalid_option)
{
    const char *args[] = {"test", "-r"};

    init_parser();
    if (add_option("-r", "--recursive", "recursive", "recursive") < 0)
        cr_assert_eq(1, 0);
    parse_args(2, args);
    cr_assert_eq(is_option_found("version"), false);
}
