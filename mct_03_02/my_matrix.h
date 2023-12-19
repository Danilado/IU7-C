#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

enum matrix_errors {
    NO_MEMORY = 1,
    BAD_INDEX,
    BAD_REALLOC,
    BAD_SIZE,
    BAD_INPUT,
};

typedef struct {
    int **columnsptr;
    size_t rows;
    size_t columns;
} my_matrix_t;

int matrix_init(my_matrix_t *mat, rows, columns);
void matrix_destroy(my_matrix_t *mat);

int matrix_remove_column(my_matrix_t *mat, size_t column);
size_t matrix_find_col_w_max(my_matrix_t *mat);

int matrix_input(my_matrix_t *mat);
void matrix_print(my_matrix_t *mat);

#endif