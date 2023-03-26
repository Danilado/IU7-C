#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1

int main(void)
{
    double start_velocity, acc, time;
    double distance;

    printf("Введите начальную скорость: ");
    if (scanf("%lf", &start_velocity) != 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите ускорение: ");
    if (scanf("%lf", &acc) != 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите время движения: ");
    if (scanf("%lf", &time) != 1)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    distance = start_velocity * time + acc * time * time / 2;

    printf("Пройденное расстояние составляет %.6lf\n", distance);
    return EXIT_SUCCESS;
}
