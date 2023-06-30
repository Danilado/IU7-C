#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1

int main(void)
{
    int number;
    int prod = 1;

    printf("Введите трёхзначное число: ");
    if (scanf("%d", &number) != 1 || number / 1000 != 0 || number / 100 == 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    // Модуль нужен для того, чтобы не возникало ошибок
    // с отрицательными числами, потому что от минуса
    // произведение цифр никак не меняется
    number = abs(number);

    while (number != 0)
    {
        prod *= number % 10;
        number /= 10;
    }

    printf("Произведение цифр числа: %d\n", prod);
    return EXIT_SUCCESS;
}
