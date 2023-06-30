#ifndef MY_ARGPARSE_H
#define MY_ARGPARSE_H

#include <string.h>

#define SORT_MODE "sb"
#define SORT_MODE_CODE 1
#define SORT_MODE_ARGC 2

#define PRINT_MODE "fb"
#define PRINT_MODE_CODE 2
#define PRINT_MODE_ARGC 2

#define ADD_MODE "ab"
#define ADD_MODE_CODE 3
#define ADD_MODE_ARGC 1

#define NO_MODE 1
#define NOT_ENOUGH_ARGS 2
#define TOO_MUCH_ARGS 3
#define BAD_MODE 4

typedef struct
{
    int mode;
    char *arg1;
    char *arg2;
} args_s;

int my_argparse(int argc, char **argv, args_s *args);

#endif
