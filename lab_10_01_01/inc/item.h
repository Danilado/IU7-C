#ifndef ITEM_H
#define ITEM_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef POSIX_C_SOURCE
#define POSIX_C_SOURCE 200809L
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_START_LEN 10
#define EPS (double)1e-6

typedef struct item_type_t *item_t;

item_t item_create(void);
void item_destroy(item_t item);
void item_print(item_t item);

enum item_scan_errors
{
    NO_ITEMS = 1,
    TOO_MANY_ITEMS,
    NO_NAME,
    NO_WEIGHT,
    BAD_WEIGHT,
    NO_VOLUME,
    BAD_VOLUME,
};

int item_scanf(item_t item, FILE *stream);

char *item_get_name(const item_t item);
double item_get_weight(const item_t item);
double item_get_volume(const item_t item);
double item_get_density(const item_t item);

void item_set_name(item_t item, char *name);
void item_set_weight(item_t item, double weight);
void item_set_volume(item_t item, double volume);
int density_comparator(const void *vi1, const void *vi2);

#endif
