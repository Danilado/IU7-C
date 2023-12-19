#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum my_snprintf_errors
{
    BAD_DST = 1,
    UNSUPPORTED_FORMAT,
    NO_MEMORY,
};

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

#endif
