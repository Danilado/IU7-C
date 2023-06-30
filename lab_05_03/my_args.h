#ifndef MY_ARGS_H
#define MY_ARGS_H

#define CREATE_MODE 'c'
#define PRINT_MODE 'p'
#define SORT_MODE 's'

#define NOT_ENOUGH_ARGS 1
#define BAD_ARG_ORDER 2
#define BAD_MODE 3
#define BAD_NUMBER 5
#define TOO_MUCH_ARGS 6

#include <stdio.h>
#include <string.h>

typedef struct
{
    char *filename;
    int mode;
    int number;
} args_s;

int parse_args(int argc, char **argv, args_s *args);

#endif
