#include "array.h"
#include "matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_EL_INPUT_ERROR 5

void int_swap(int *first, int *second)
{
    int tmp = *second;
    *second = *first;
    *first = tmp;
}

void find_row_mins(arr_t dst, matrix_t src, size_t r, size_t c)
{
    for (size_t i = 0; i < r; ++i)
    {
        int rowmin = src[i][0];

        for (size_t j = 1; j < c; ++j)
            if (src[i][j] < rowmin)
                rowmin = src[i][j];

        dst[i] = rowmin;
    }
}

void save_order_sort(arr_t order, arr_t arr, size_t alen)
{
    for (size_t i = 0; i < alen - 1; ++i)
        for (size_t j = 0; j < alen - 1; ++j)
            if (arr[j] < arr[j + 1])
            {
                int_swap(&arr[j], &arr[j + 1]);
                int_swap(&order[j], &order[j + 1]);
            }
}

void matrix_mv_rows(arr_t ord, matrix_t dst, matrix_t src, size_t r, size_t c)
{
    for (size_t i = 0; i < r; ++i)
        for (size_t j = 0; j < c; j++)
            dst[i][j] = src[ord[i]][j];
}

int main(void)
{
    matrix_t matrix, answer;
    arr_t mins, order;
    size_t rows, columns;

    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%zu", &rows) != 1)
    {
        puts("Ошибка ввода количества строк");
        return ROW_COUNT_INPUT_ERROR;
    }
    if (rows == 0 || rows > ROWMAX)
    {
        puts("Неверно введено количество строк");
        return BAD_ROW_COUNT_ERROR;
    }

    if (scanf("%zu", &columns) != 1)
    {
        puts("Ошибка ввода количества столбцов");
        return COL_COUNT_INPUT_ERROR;
    }
    if (columns == 0 || columns > COLMAX)
    {
        puts("Неверно введено количество столбцов");
        return BAD_COL_COUNT_ERROR;
    }

    printf("Введите матрицу: \n");
    if (matrix_scan(matrix, rows, columns) != rows * columns)
    {
        puts("Ошибка ввода элемента матрицы");
        return MATRIX_EL_INPUT_ERROR;
    }

    arr_fill(order, rows);
    find_row_mins(mins, matrix, rows, columns);

    save_order_sort(order, mins, rows);

    matrix_mv_rows(order, answer, matrix, rows, columns);

    printf("Полученная матрица: \n");
    matrix_print(answer, rows, columns);

    return EXIT_SUCCESS;
}
