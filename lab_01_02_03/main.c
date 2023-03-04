#include <math.h>
#include <stdio.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define PI acos(-1)

int main(void)
{
    double a, b;
    double phi;

    double area;

    printf("Введите значение стороны a: ");
    if (scanf("%lf", &a) != 1 || a <= 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите значение стороны b: ");
    if (scanf("%lf", &b) != 1 || b <= 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите угол фи между сторонами треугольника в градусах: ");
    if (scanf("%lf", &phi) != 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    area = a * b * sin(phi / 180 * PI) / 2;

    printf("Площадь треугольника: %.6lf\n", area);
    return EVERYTHING_OK;
}
