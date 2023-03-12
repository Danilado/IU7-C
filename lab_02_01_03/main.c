#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#define NMAX 10

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define NO_POS_ELEMENTS_ERROR 2

typedef double arr[NMAX];

int main(void)
{
    arr a;
    size_t alen = 0, pos_count = 0;
    double prod = 1, geom_mean;

    printf("Введите длину массива: ");
    if (scanf("%zu", &alen) != 1 || alen <= 0 || alen > 10)
    {
        printf("Ошибка ввода\n");
        return INPUT_ERROR;
    }

    for (size_t i = 0; i < alen; ++i)
    {
        printf("Введите элемент массива: ");
        if (scanf("%lf", &a[i]) != 1)
        {
            printf("Ошибка ввода\n");
            return INPUT_ERROR;
        }
    }

    for (size_t i = 0; i < alen; ++i)
        if (a[i] > 0)
        {
            ++pos_count;
            prod *= a[i];
        }

    if (!pos_count)
    {
        printf("В массиве нет положительных элементов!\n");
        return NO_POS_ELEMENTS_ERROR;
    }

    geom_mean = pow(prod, (double)1 / pos_count);

    printf("Среднее геометрическое положительных элементов массива: ");
    printf("%.6lf\n", geom_mean);

    return EVERYTHING_OK;
}
