#include <math.h>
#include <stdio.h>

#define INPUT_ERROR 1
#define PI acos(-1)

int main(void)
{
    double a, b;
    double phi;

    double area;

    printf("Введите значения сторон a и b: ");
    if (scanf("%lf%lf", &a, &b) != 2 || a <= 0 || b <= 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите угол фи между сторонами треугольника: ");
    if (scanf("%lf", &phi) != 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    area = a * b * sin(phi / 180 * PI) / 2;

    printf("Вычисленная площадь треугольника: %.6lf\n", area);
    return 0;
}
