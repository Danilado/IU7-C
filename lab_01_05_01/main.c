#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1

void divmod(long long a, long long d, long long *q, long long *r)
{
    *q = 0;
    *r = 0;
    while (a >= d)
    {
        ++*q;
        a -= d;
    }
    *r = a;

    return;
}

int main(void)
{
    long long a, d;
    long long q = 0, r = 0;

    printf("Введите числитель и знаменатель: ");
    if (scanf("%lld%lld", &a, &d) != 2 || a <= 0 || d <= 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    divmod(a, d, &q, &r);

    printf("Целая часть деления: %lld\nОстаток от деления: %lld\n", q, r);

    return 0;
}
