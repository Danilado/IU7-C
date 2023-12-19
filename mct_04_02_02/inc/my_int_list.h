#ifndef MY_INT_LIST_H
#define MY_INT_LIST_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int_node *node_t;
struct int_node {
  int data;
  node_t next;
};

node_t node_create(int data);

void node_destroy(node_t *node);

void list_clear(node_t *head);

node_t list_get_3rd_min(node_t head);

node_t list_get_max(node_t head);

void list_print(node_t head);

int list_push(node_t *head, int data);

int list_remove(node_t *head, node_t node);

size_t list_get_length(node_t head);

int list_swap_max_2nd(node_t *head);

#endif