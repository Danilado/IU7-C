#ifndef MY_ARR_H
#define MY_ARR_H

#include <stdlib.h>

enum arr_errors {
    NO_MEMORY = 1,
};

typedef struct {
    int* base;
    size_t capacity;
    size_t el_count;
} my_arr_t;

int arr_init(my_arr_t *arr, size_t el_count);
void arr_destroy(my_arr_t *arr);

int arr_push(my_arr_t *arr, int value);

int arr_minimize(my_arr_t *arr);

int arr_remove_divisable(my_arr_t *arr, unsigned divisor);

void arr_print(my_arr_t *arr);

#endif
