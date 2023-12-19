#ifndef ITEM_H
#define ITEM_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef POSIX_C_SOURCE
#define POSIX_C_SOURCE 200809L
#endif

#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum poly_input_errors
{
    POLY_BAD_K_INPUT = 1,
    POLY_BAD_LEN_INPUT,
};

int poly_list_scanf(node_t **head);
void pow_destroy(node_t *node);

int poly_list_get_value(const node_t *head, int var);
node_t *poly_list_derivative(const node_t *head);
node_t *poly_list_sum(const node_t *head1, const node_t *head2);
int poly_list_split(node_t *src_head, node_t **odd, node_t **even);

void poly_list_printf(const node_t *head);

#endif
