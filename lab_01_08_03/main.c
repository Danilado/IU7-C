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
    uint64_t res1 = 0, res2 = 0;
    if (num == 0)
    {
        for (int i = 0; i < 32; ++i)
            printf("0");
        return;
    }

    for (int i = 0; i < 16; ++i)
    {
        res1 += (uint64_t)(num % 2) * (uint64_t)pow(10, i);
        num /= 2;
    }

    for (int i = 0; i < 16; ++i)
    {
        res2 += (uint64_t)(num % 2) * (uint64_t)pow(10, i);
        num /= 2;

        printf("%d", (int)(res1 % 10));
        res1 /= 10;
    }

    for (int i = 0; i < 16; ++i)
    {
        printf("%d", (int)(res2 % 10));
        res2 /= 10;
    }
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

    // printf("Encrypted num: %u", encrypted_num);
    printf("Result: ");

    print_bin(encrypted_num);

    printf("\n");

    return 0;
}
