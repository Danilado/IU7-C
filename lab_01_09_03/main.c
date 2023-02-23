#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

// Функция добавлена из-за требования 4 ко второй части лабораторной
int count_mul(double *mul)
{
    double n;

    printf("Введите x1: ");
    if (scanf("%lf", &n) == 0 || n < 0)
    {
        printf("Введите хотя бы одно число");
        return INPUT_ERROR;
    }

    for (long i = 1; n >= 0; ++i)
    {
        *mul *= (i + n);

        printf("Введите следующее число: ");
        if (scanf("%lf", &n) == 0)
        {
            printf("Ошибка ввода!");
            return INPUT_ERROR;
        }
    }

    return 0;
}

int main(void)
{
    double mul = 1, answer;
    int rc;

    rc = count_mul(&mul);

    if (rc != 0)
        return rc;

    answer = exp(1 / mul);

    printf("Вычисленное значение g(x): %lf\n", answer);

    return 0;
}
