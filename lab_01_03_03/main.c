#include <stdio.h>

#define INPUT_ERROR 1

int main(void)
{
    double start_speed, acc, time;
    double distance;

    printf("Введите начальную скорость объекта: ");
    if (!(scanf("%lf", &start_speed) == 1))
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите ускорение объекта: ");
    if (!(scanf("%lf", &acc) == 1))
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    printf("Введите время движения объекта: ");
    if (!(scanf("%lf", &time) == 1))
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    distance = start_speed * time + acc * time * time / 2;

    printf("Расстояние, пройденное объектом составляет %lf\n", distance);
    return 0;
}
