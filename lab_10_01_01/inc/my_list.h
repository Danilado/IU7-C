#ifndef MY_LIST_H
#define MY_LIST_H

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

enum list_errors
{
    LIST_NO_MEMORY = 1,
    LIST_BAD_INDEX,
    LIST_NO_HEAD,
};

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

void list_destroy(node_t **head);
size_t list_get_length(const node_t *head);

void list_push(node_t **head, node_t *node);
int list_push_value(node_t **head, void *value);
void list_unshift(node_t **head, node_t *node);
int list_unshift_value(node_t **head, void *value);
int list_insert(node_t **head, node_t *node, size_t index);
int list_insert_value(node_t **head, void *value, size_t index);

node_t *list_pop(node_t **head);
node_t *list_shift(node_t **head);
// изначально было remove_by_index, но это очень длинно
node_t *list_remove(node_t **head, size_t index);
// изначально было get_by_index, но это очень длинно
node_t *list_get(const node_t *head, size_t index);

// ***

node_t *node_create(void *data);
void node_destroy(node_t *node);
void *node_get_data(node_t *node);

// ***

void list_apply(node_t *head, void (*func)(node_t *));

// ЗАДАНИЯ ПО ВЫБОРУ

// 1 балл
// clang-format off
node_t *find(node_t *head, const void *data, 
int (*comparator)(const void *, const void *));
// clang-format on
// 1 балл
void *pop_front(node_t **head);
// 1 балл
void *pop_back(node_t **head);
// 2 балла
void insert(node_t **head, node_t *elem, node_t *before);

// 1 балл
int copy(node_t *head, node_t **new_head);
// 1 балл
void append(node_t **head_a, node_t **head_b);

// 4 балла - сортировка слиянием
void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b,
int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif