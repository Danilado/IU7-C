#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define EVERYTHING_OK 0
#define INPUT_ERROR 1

// 01010101....
#define ODD_BITS 1431655765
// 10101010....
#define EVEN_BITS 2863311530

uint32_t encrypt(uint32_t num)
{
    uint32_t odd_part, even_part;

    odd_part = ODD_BITS & num;
    even_part = EVEN_BITS & num;

    odd_part = odd_part << 1;
    even_part = even_part >> 1;

    return odd_part | even_part;
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
    if (scanf("%" SCNu32, &number) != 1)
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
