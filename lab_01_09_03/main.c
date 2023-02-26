#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define ZERO_LENGTH_SEQUENCE 2

int g_x(double *answer)
{
    double n, prod = 1;

    printf("Введите первое значение x: ");
    if (scanf("%lf", &n) != 1 || n < 0)
    {
        printf("Введите хотя-бы одно число!\n");
        return ZERO_LENGTH_SEQUENCE;
    }

    for (int i = 1; n >= 0; ++i)
    {
        prod *= (i + n);

        printf("Введите следующее число: ");
        if (scanf("%lf", &n) != 1)
        {
            printf("Ошибка ввода!\n");
            return INPUT_ERROR;
        }
    }

    *answer = exp(1 / prod);

    return EVERYTHING_OK;
}

int main(void)
{
    double answer;
    int rc;

    rc = g_x(&answer);

    if (rc != 0)
        return rc;

    printf("Вычисленное значение g(x): %.6lf\n", answer);

    return EVERYTHING_OK;
}
