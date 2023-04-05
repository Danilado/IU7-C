#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_NOT_SQUARE_ERROR 5
#define MATRIX_EL_INPUT_ERROR 6

void int_swap(int *first, int *second)
{
    int tmp = *second;
    *second = *first;
    *first = tmp;
}

void swap_vertical_areas(matrix_t mat, size_t r)
{
    for (size_t i = 0; i < r / 2 + r % 2; ++i)
        for (size_t j = 0; j <= i; ++j)
        {
            int_swap(&mat[i][j], &mat[i][r - j - 1]);
            if (i != r - i - 1)
                int_swap(&mat[r - i - 1][j], &mat[r - i - 1][r - j - 1]);
        }
}

int main(void)
{
    matrix_t matrix;
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

    if (columns != rows)
    {
        puts("Не квадратные матрицы не поддерживаются");
        return MATRIX_NOT_SQUARE_ERROR;
    }

    printf("Введите матрицу: \n");
    if (matrix_scan(matrix, rows, columns) != rows * columns)
    {
        puts("Ошибка ввода элемента матрицы");
        return MATRIX_EL_INPUT_ERROR;
    }

    swap_vertical_areas(matrix, rows);

    printf("Полученная матрица:\n");
    matrix_print(matrix, rows, columns);

    return EXIT_SUCCESS;
}
