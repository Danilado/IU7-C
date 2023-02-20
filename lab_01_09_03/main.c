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
    for (long i = 1; scanf("%lf", &n) == 1; ++i)
    {
        if (n < 0)
        {
            if (i == 1)
            {
                printf("Введите хотя бы одно число");
                return INPUT_ERROR;
            }
            break;
        }

        mul *= (i + n);
        printf("Введите x%ld: ", i + 1);
    }

    answer = exp(1 / mul);

    printf("Вычисленное значение g(x): %lf", answer);

    return 0;
}
