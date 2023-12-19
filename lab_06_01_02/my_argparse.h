#ifndef MY_ARGPARSE_H
#define MY_ARGPARSE_H

#include <string.h>

enum argparse_errors
{
    NO_FILENAME_ERROR = 1,
    TOO_MANY_ARGS,
};

enum prefix_modes
{
    SORT_N_PRINT,
    PRINT_ALL,
    CHECK_PREFIX,
};

#define PRINT_ALL_PREFIX "ALL"

typedef struct
{
    int mode;
    char *filename;
    char *prefix;
} args_t;

int my_argparse(int argc, char **argv, args_t *args);

#endif
