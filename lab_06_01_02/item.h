#ifndef ITEM_H
#define ITEM_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_ITEM_NAME_LEN 25
#define MAX_ITEM_COUNT 15
#define EPS (double)1e-6

typedef char limited_string[MAX_ITEM_NAME_LEN + 1];

typedef struct
{
    limited_string name;
    double weight;
    double volume;
} item_t;

typedef item_t item_arr_t[MAX_ITEM_COUNT];

void item_print(item_t *item);

enum item_scan_errors
{
    NO_ITEMS = 1,
    TOO_MANY_ITEMS,
    NO_NAME,
    BAD_NAME,
    TOO_LONG_NAME,
    NO_WEIGHT,
    BAD_WEIGHT,
    NO_VOLUME,
    BAD_VOLUME,
};

int item_name_scan(limited_string dst, FILE *stream);

int item_scan(item_t *item, FILE *stream);

int item_arr_scan(item_arr_t dst, size_t *len, FILE *stream);

size_t pref_items_print(item_arr_t src, size_t items_len, char *prefix);

bool density_comparator(item_t *i1, item_t *i2);

void sort_by_density(item_arr_t arr, size_t alen);

#endif
