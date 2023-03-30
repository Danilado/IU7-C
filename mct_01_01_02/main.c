#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define X_INPUT_ERROR 1
#define EPS_INPUT_ERROR 2

double series(double x, double eps)
{
    double sum = -x / (2 * 5 * 4 * 3 * 2 - 4 * 3 * 2);
    double cur_el = sum;

    for (int i = 4; fabs(cur_el) >= eps; ++i)
    {
        cur_el *= x * (2 * i + 1) / (i + 1) / (2 * i + 3);
        sum += cur_el;
    }

    return sum;
}

int main(void)
{
    double x, eps;
    double ans, cos_asin;

    printf("Введите значение x: ");
    if (scanf("%lf", &x) != 1)
        return X_INPUT_ERROR;

    printf("Введите значение eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0)
        return EPS_INPUT_ERROR;

    ans = series(x, eps);
    cos_asin = cos(asin(x));

    printf("Сумма ряда: %.6le\n", ans);
    printf("Значение через встроенные функции: %+.5lf\n", cos_asin);

    return EXIT_SUCCESS;
}
