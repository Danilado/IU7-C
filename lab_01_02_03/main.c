#include <math.h>
#include <stdio.h>

#define PI acos(-1)

int main()
{
    float a, b;
    float phi;

    float area;

    printf("Введите значения сторон a и b: ");
    scanf("%g%g", &a, &b);

    printf("Введите угол фи между сторонами треугольника: ");
    scanf("%g", &phi);

    area = a * b * sin(phi / 180 * PI) / 2;

    printf("Вычисленная площадь треугольника: %g\n", area);
    return 0;
}
