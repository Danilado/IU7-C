#ifndef MY_ARGPARSE_H
#define MY_ARGPARSE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGS 2 + 1
#define MAX_ARGS 3 + 1

enum argparse_errors
{
    NOT_ENOUGH_ARGS = 1,
    TOO_MUCH_ARGS,
    INVALID_INPUT_FILE,
    INVALID_OUTPUT_FILE,
    INVALID_3RD_ARG,
};

typedef struct
{
    FILE *file_in;
    FILE *file_out;
    bool filter;
} args_t;

int my_argparse(int argc, char **argv, args_t *dst);

#endif
