#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

int main(void)
{
    double mul = 1, n, answer;

    printf("Введите x1: ");
    if (scanf("%lf", &n) != 1 || n < 0)
    {
        printf("Введите хотя бы одно число");
        return INPUT_ERROR;
    }

    for (long i = 1; n >= 0; ++i)
    {
        mul *= (i + n);

        printf("Введите x%ld: ", i + 1);
        if (scanf("%lf", &n) != 1)
        {
            printf("Ошибка ввода!");
            return INPUT_ERROR;
        }
    }

    answer = exp(1 / mul);

    printf("Вычисленное значение g(x): %lf\n", answer);

    return 0;
}
