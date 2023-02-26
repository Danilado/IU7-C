#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

uint32_t encrypt(uint32_t num)
{
    uint32_t odd_bits, even_bits;

    // это не совсем костанты, чтобы не вводить
    // ещё две переменные, я использую те, которые изначально
    // обхявляю как маски. Я решил переименовать их, чтобы
    // обосновать свою позицию.

    // 01010101....
    odd_bits = 1431655765;
    // 10101010....
    even_bits = 2863311530;

    odd_bits = odd_bits & num;
    even_bits = even_bits & num;

    odd_bits = odd_bits << 1;
    even_bits = even_bits >> 1;

    return odd_bits | even_bits;
}

void print_bin(uint32_t num)
{
    for (uint32_t cur_bit = (uint32_t)1 << 31; cur_bit > 0; cur_bit >>= 1)
        printf("%d", !!(num & cur_bit));

    return;
}

int main(void)
{
    uint32_t number, encrypted_num;

    printf("Введите число для шифрования: ");
    if (scanf("%u", &number) != 1)
    {
        printf("Error: Неправильный ввод!\n");
        return INPUT_ERROR;
    }

    encrypted_num = encrypt(number);

    printf("Result: ");

    print_bin(encrypted_num);

    printf("\n");

    return EVERYTHING_OK;
}
