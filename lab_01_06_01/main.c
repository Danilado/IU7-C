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

double calculate_side(double xa, double ya, double xb, double yb)
{
    return sqrt(pow(xb - xa, 2) + pow(yb - ya, 2));
}

double find_area(
double xa, double ya, double xb, double yb, double xc, double yc)
{
    double side_a = calculate_side(xa, ya, xb, yb);
    double side_b = calculate_side(xb, yb, xc, yc);
    double side_c = calculate_side(xa, ya, xc, yc);
    double p = (side_a + side_b + side_c) / 2;

    return sqrt(p * (p - side_a) * (p - side_b) * (p - side_c));
}

int main(void)
{
    double xa, xb, xc, ya, yb, yc;
    double area;

    printf("Введите координаты 1-й точки: ");
    if (!scanf("%lf%lf", &xa, &ya))
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    printf("Введите координаты 2-й точки: ");
    if (!scanf("%lf%lf", &xb, &yb) || compare_points(xa, ya, xb, yb))
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    printf("Введите координаты 3-й точки: ");
    if (!scanf("%lf%lf", &xc, &yc) || compare_points(xa, ya, xc, yc) ||
        compare_points(xb, yb, xc, yc))
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    area = find_area(xa, ya, xb, yb, xc, yc);
    if (area < EPS)
    {
        printf("Too small of a triangle");
        return RUNTIME_ERROR;
    }
    printf("Вычисленная площадь треугольника: %.6lf\n", area);

    return 0;
}
