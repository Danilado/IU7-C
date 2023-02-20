#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

double mysin(double x, double eps)
{
    double sum = x;
    double next_el;

    double xpow = x;
    long long divider_fact = 1;
    bool minus_flag = 1;

    for (int i = 3; 1; i += 2)
    {
        divider_fact *= i * (i - 1);
        xpow *= x * x;

        next_el = xpow / divider_fact * pow(-1, minus_flag);
        sum += next_el;

        if (fabs(next_el) < eps)
            break;

        minus_flag = !minus_flag;
    }

    return sum;
}

int main(void)
{
    double x, eps;
    double perfect_value, calculated_value;
    double absolute_error, relative_error;

    printf("Введите значение переменной x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    printf("Введите значение переменной eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0 || eps > 1)
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    perfect_value = sin(x);
    calculated_value = mysin(x, eps);

    absolute_error = fabs(perfect_value - calculated_value);
    if (fabs(perfect_value) < 1e-8)
        relative_error = 0;
    else
        relative_error = absolute_error / fabs(perfect_value);

    printf("Вычисленное идеальное значение: %lf\n", perfect_value);
    printf("Вычисленное через ряд значение: %lf\n", calculated_value);
    printf("Абсолютная погрешность: %lf\n", absolute_error);
    printf("Относительная погрешность: %lf\n", relative_error);

    return 0;
}
