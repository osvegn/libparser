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
