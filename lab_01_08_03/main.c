#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define INPUT_ERROR 1
#define RUNTIME_ERROR 2

uint32_t encrypt(uint32_t num)
{
    uint32_t mask1, mask2;

    // 01010101....
    mask1 = 1431655765;
    // 10101010....
    mask2 = 2863311530;

    mask1 = mask1 & num;
    mask2 = mask2 & num;

    mask1 = mask1 << 1;
    mask2 = mask2 >> 1;

    return mask1 | mask2;
}

void print_bin(uint32_t num)
{
    for (uint64_t mask = 2147483648; mask > 0; mask /= 2)
    {
        if ((uint32_t)(num & mask) == 0)
            printf("0");
        else
            printf("1");
    }

    return;
}

int main(void)
{
    uint32_t number, encrypted_num;

    printf("Введите число для шифрования: ");
    if (scanf("%u", &number) != 1)
    {
        printf("Error: Incorrect Input\n");
        return INPUT_ERROR;
    }

    encrypted_num = encrypt(number);
    printf("Encrypted num: %u\n", encrypted_num);

    printf("Result: ");

    print_bin(encrypted_num);

    printf("\n");

    return 0;
}
