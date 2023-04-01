#include "./matrixes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_COUNT_INPUT_ERROR 1
#define BAD_ROW_COUNT_ERROR 2
#define COL_COUNT_INPUT_ERROR 3
#define BAD_COL_COUNT_ERROR 4
#define MATRIX_EL_INPUT_ERROR 5
#define CHECKER_DIGIT_INPUT_ERROR 6
#define BAD_CHECKER_DIGIT_ERROR 7
#define NOTHING_TO_OUTPUT_ERROR 8

bool digit_in(int num, int digit)
{
    num = abs(num);
    do
    {
        if (num % 10 == digit)
            return true;
        num /= 10;
    } while (num != 0);
    return false;
}

bool check_col(matrix_t matrix, size_t rows, size_t columnn, int digit)
{
    for (size_t i = 0; i < rows; ++i)
        if (digit_in(matrix[i][columnn], digit))
            return true;
    return false;
}

void filter_matrix(matrix_t matrix, size_t rows, size_t *columns, int dig)
{
    for (size_t j = *columns; j > 0; --j)
        if (check_col(matrix, rows, j - 1, dig))
            *columns = matrix_remove_col(matrix, rows, *columns, j - 1);
}

int main(void)
{
    matrix_t matrix;
    size_t rows, columns;
    int digit;

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

    printf("Введите число для проверки столбцов: ");
    if (scanf("%d", &digit) != 1)
    {
        puts("Ошибка ввода цифры для проверки столбцов");
        return CHECKER_DIGIT_INPUT_ERROR;
    }
    if (digit < 0 || digit > 9)
    {
        puts("Введена не цифра");
        return BAD_CHECKER_DIGIT_ERROR;
    }

    filter_matrix(matrix, rows, &columns, digit);

    if (!columns)
    {
        puts("Вся матрица была стёрта");
        return NOTHING_TO_OUTPUT_ERROR;
    }

    puts("Полученная матрица: ");
    matrix_print(matrix, rows, columns);

    return EXIT_SUCCESS;
}
