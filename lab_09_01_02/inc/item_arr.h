#ifndef ITEM_ARR_H
#define ITEM_ARR_H

#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct item_arr_type_t *item_arr_t;

enum item_arr_errors
{
    NO_MEMORY = 1,
    BAD_BASE_REALLOC,
};

item_arr_t item_arr_create(void);
void item_arr_destroy(item_arr_t arr);
int item_arr_expand(item_arr_t arr);
int item_arr_minimize(item_arr_t arr);

size_t item_arr_get_length(item_arr_t arr);
size_t item_arr_get_capacity(item_arr_t arr);
item_t item_arr_get_by_index(item_arr_t arr, size_t index);

int item_arr_push(item_arr_t arr, item_t item);

int item_arr_scanf(item_arr_t dst, FILE *stream);
size_t pref_items_print(const item_arr_t arr, char *prefix);

void sort_by_density(item_arr_t arr);

#endif