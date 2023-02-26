#include <stdio.h>
#include <stdlib.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

int divide(int a, int d, int *r)
{
    int q = 0;
    *r = 0;
    while (a >= d)
    {
        ++q;
        a -= d;
    }
    *r = a;

    return q;
}

int main(void)
{
    int a, d;
    int q = 0, r = 0;

    printf("Введите числитель и знаменатель: ");
    if (scanf("%d%d", &a, &d) != 2 || a <= 0 || d <= 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    q = divide(a, d, &r);

    printf("Целая часть деления: %d\nОстаток от деления: %d\n", q, r);

    return EVERYTHING_OK;
}
