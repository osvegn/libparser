#include <criterion/criterion.h>
#include "parser.h"

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
    char *args[] = {"test", "--version"};

    init_parser();
    if (add_option("-v", "--version", "version", "") < 0)
        return;
    parse_args(2, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    del_parser();
}

Test(parse_args, parser_one_arg_two_options)
{
    char *args[] = {"test", "--quit"};

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
    char *args[] = {"test", "--version", "vers"};

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
    char *args[] = {"test", "--version", "vers"};

    init_parser();
    if (add_option("-v", "--version", "version", NULL) < 0)
        return;
    parse_args(3, args);
    cr_assert_eq(get_parser()->options[1].found, true);
    del_parser();
}

Test(parse_args, parser_one_arg_one_option_with_value_and_short_option)
{
    char *args[] = {"test", "-v", "vers"};

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
    char *args[] = {"test", "--version=salut"};

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
    char *args[] = {"test", "--load", "-v", "--help", "coucou", "--test"};

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