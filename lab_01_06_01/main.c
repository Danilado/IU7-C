#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-8
#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

bool compare_points(double xa, double ya, double xb, double yb)
{
    return ((fabs(xa - xb) < EPS) && (fabs(ya - yb) < EPS));
}

double vecmul(double xa, double ya, double xb, double yb, double xc, double yc)
{
    return fabs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya)) / 2;
}

int main(void)
{
    double xa, xb, xc, ya, yb, yc;
    double area;

    printf("Введите координаты 1-й точки: ");
    if (scanf("%lf%lf", &xa, &ya) != 2)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите координаты 2-й точки: ");
    if (scanf("%lf%lf", &xb, &yb) != 2)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    if (compare_points(xa, ya, xb, yb))
    {
        printf("Ошибка! Две точки совпадают!\n");
        return RUNTIME_ERROR;
    }

    printf("Введите координаты 3-й точки: ");
    if (scanf("%lf%lf", &xc, &yc) != 2)
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    if (compare_points(xa, ya, xc, yc) || compare_points(xb, yb, xc, yc))
    {
        printf("Ошибка! Две точки совпадают!\n");
        return RUNTIME_ERROR;
    }

    area = vecmul(xa, ya, xb, yb, xc, yc);

    if (area < EPS)
    {
        printf("Точки скорее всего стоят на одной прямой!\n");
        return RUNTIME_ERROR;
    }

    printf("Вычисленная площадь треугольника: %.6lf\n", area);

    return 0;
}
