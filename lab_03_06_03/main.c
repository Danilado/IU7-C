#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_NOT_SQUARE_ERROR 5

void matrix_spiral_fill(matrix_t matrix, size_t rows, size_t columns)
{
    int addition = 0;
    for (size_t i = 0; i < rows / 2 + rows % 2; ++i)
    {
        // Сохраняем кол-во элементов, записанных на следующих слоях
        if (i > 0)
            addition += (rows + columns - 4 * i + 2) * 2;

        // clang-format off
        for (size_t j = i; j < rows - i; ++j)
        {
            matrix[j][i] = addition - i + j + 1;
            matrix[columns - j - 1][rows - i - 1] =
                addition + j + columns - 5 * i + rows - 1;
        }

        for (size_t j = i + 1; j < rows - i - 1; ++j)
        {
            // 2 * rows + columns - 7i <- прошли три четверти спирали
            matrix[i][columns - j - 1] =
                addition + 2 * rows + columns - 7 * i + j - 2;
            // rows - 2i <- прошли одну четверть спирали
            matrix[rows - i - 1][j] = addition + rows - 3 * i + j;
        }
        // clang-format on
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

    if (rows != columns)
    {
        puts("Не квадратные матрицы не поддерживаются");
        return MATRIX_NOT_SQUARE_ERROR;
    }

    matrix_spiral_fill(matrix, rows, columns);

    printf("Заполненная матрица:\n");
    matrix_print(matrix, rows, columns);

    return 0;
}
