#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

double mysin(double x, double eps)
{
    double sum = x;
    double cur_el;

    cur_el = x;

    // начинаем с 3 и шагаем по 2,
    // чтобы удобнее считать факториал в знаменателе
    for (int i = 3; fabs(cur_el) >= eps; i += 2)
    {
        cur_el = -1 * cur_el * x * x / i / (i - 1);
        sum += cur_el;
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
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите значение переменной eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0 || eps > 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    // Значение, разумеется, не "идеальное", просто встроенные функции,
    // как правило, довольно точны.
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

    return EVERYTHING_OK;
}
