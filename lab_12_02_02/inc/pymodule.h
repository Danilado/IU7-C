#ifndef MY_PY_MODULE
#define MY_PY_MODULE

#include <stdbool.h>
#include <stdlib.h>

#define TOO_MUCH 1

int arr_fib_fill(int *dst, size_t amount);

size_t arr_unique(int *src, size_t el_count, int *dst);

#endif