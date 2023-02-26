#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-8
#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define EQUAL_POINTS_ERROR 2
#define POINTS_FORM_LINE_ERROR 3

bool is_equal(double xa, double ya, double xb, double yb)
{
    return ((fabs(xa - xb) < EPS) && (fabs(ya - yb) < EPS));
}

// clang-format off

/*
    Считаем векторное произведение. За векторы беру
    AB и AC, то есть точка a - точка их начал

    Комментарии, начинающиеся с "clang-format" нужны для
    управления форматировщиком, который мешает правильно
    отформатировать объявление функции
*/
double vecprod(double xa, double ya, // координаты точки a
double xb, double yb, // координаты точки b
double xc, double yc) // координаты точки c
{
    return fabs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));
}

// clang-format on

int main(void)
{
    double xa, xb, xc, ya, yb, yc;
    double area;

    printf("Введите координаты точки a: ");
    if (scanf("%lf%lf", &xa, &ya) != 2)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите координаты точки b: ");
    if (scanf("%lf%lf", &xb, &yb) != 2)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    if (is_equal(xa, ya, xb, yb))
    {
        printf("Две точки совпадают!\n");
        return EQUAL_POINTS_ERROR;
    }

    printf("Введите координаты точки c: ");
    if (scanf("%lf%lf", &xc, &yc) != 2)
    {
        printf("Ошибка ввода!");
        return INPUT_ERROR;
    }

    if (is_equal(xa, ya, xc, yc) || is_equal(xb, yb, xc, yc))
    {
        printf("Две точки совпадают!\n");
        return EQUAL_POINTS_ERROR;
    }

    // векторное произведение - площадь параллелограмма
    // площадь треугольника - площадь параллелограмма пополам
    area = vecprod(xa, ya, xb, yb, xc, yc) / 2;

    if (area < EPS)
    {
        printf("Точки стоят на одной прямой!\n");
        return POINTS_FORM_LINE_ERROR;
    }

    printf("Площадь треугольника: %.6lf\n", area);

    return EVERYTHING_OK;
}
