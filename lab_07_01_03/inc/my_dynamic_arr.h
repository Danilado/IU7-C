#ifndef MY_DYNAMIC_ARR_H
#define MY_DYNAMIC_ARR_H

#include <memory.h>
#include <stdlib.h>

typedef struct
{
    void *pb;
    void *pe;
    size_t el_size;
} my_dyn_arr_t;

enum dyn_arr_errors
{
    NOT_ENOUGH_MEMORY = 1,
};

int dyn_arr_init(size_t el_size, size_t el_count, my_dyn_arr_t *dst);
void dyn_arr_destroy(my_dyn_arr_t *arr);

#endif
