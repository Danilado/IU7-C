#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1

int main(void)
{
    int number;
    int mul = 1;

    printf("Введите трёхзначное число: ");
    if (scanf("%d", &number) != 1 || number / 1000 != 0 || number / 100 == 0)
    {
        printf("Ошибка ввода!\n");
        return INPUT_ERROR;
    }

    number = abs(number);

    while (number != 0)
    {
        mul *= number % 10;
        number /= 10;
    }

    printf("Произведение цифр числа: %d\n", mul);
    return 0;
}
