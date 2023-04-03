#include "./matrixes.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4

void matrix_spiral_fill(matrix_t matrix, size_t rows, size_t columns)
{
    int addition = 0;
    for (size_t i = 0; i < rows / 2 + rows % 2; ++i)
    {
        if (i > 0)
            addition += (rows + columns - 4 * i + 2) * 2;

        for (size_t j = i; j < rows - i; ++j)
        {
            matrix[j][i] = addition - i + j + 1;
            matrix[columns - j - 1][rows - i - 1] =
            addition - i + j + columns - 4 * i + rows - 1;
        }

        for (size_t j = i + 1; j < rows - i - 1; ++j)
        {
            matrix[i][columns - j - 1] =
            addition + (rows - 2 * i) * 2 + (columns - 2 * i) + j - 2;
            matrix[rows - i - 1][j] = addition + rows - 2 * i + j;
        }
    }
}

int main(void)
{
    matrix_t matrix = {{0}};
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

    matrix_spiral_fill(matrix, rows, columns);

    printf("Заполненная матрица:\n");
    matrix_print(matrix, rows, columns);

    return 0;
}
