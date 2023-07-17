#include <boolean.h>

typedef struct option_s {
    char short_name[256];
    char long_name[512];
    char key[256];
    bool found;
} option_t;

typedef struct parser_s {
    option_t *options;
    int option_count;
} parser_t;
