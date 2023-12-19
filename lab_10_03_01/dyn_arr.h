#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dyn_arr *dyn_arr_t;

enum dyn_arr_errors
{
    NO_MEMORY = 1,
    BAD_BASE_REALLOC,
};

dyn_arr_t dyn_arr_create(void);
void dyn_arr_destroy(dyn_arr_t arr);
int dyn_arr_expand(dyn_arr_t arr);
int dyn_arr_minimize(dyn_arr_t arr);

size_t dyn_arr_get_length(dyn_arr_t arr);
size_t dyn_arr_get_capacity(dyn_arr_t arr);
void *dyn_arr_get_by_index(dyn_arr_t arr, size_t index);
void dyn_arr_remove_by_index(dyn_arr_t arr, size_t index);
void dyn_arr_set_by_index(dyn_arr_t arr, size_t index, void *value);

int dyn_arr_push(dyn_arr_t arr, void *item);

#endif