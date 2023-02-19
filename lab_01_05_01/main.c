#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1

void divmod(int a, int d, int *q, int *r)
{
    *q = 0;
    *r = 0;
    while (a >= d)
    {
        *q += 1;
        a -= d;
    }
    *r = a;

    return;
}

int main(void)
{
    int a, d;
    int q = 0, r = 0;

    printf("Введите числитель и знаменатель: ");
    if (!scanf("%d%d", &a, &d) || a <= 0 || d <= 0)
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    divmod(a, d, &q, &r);

    printf("Целая часть деления: %d\nОстаток от деления: %d\n", q, r);

    return 0;
}
