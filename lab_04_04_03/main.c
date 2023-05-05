#include "my_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_SYMBOLS " \t"
#define DIGITS "0123456789"

bool is_phone_number(char *str)
{
    char *pcur = str;
    int tmp;

    if (*pcur != '+')
        return false;

    ++pcur;

    tmp = strspn(pcur, DIGITS);
    if (!tmp)
        return false;

    pcur += tmp;

    if (strlen(pcur) != 15)
        return false;

    if (*pcur != '(')
        return false;

    ++pcur;

    tmp = strspn(pcur, DIGITS);
    if (tmp != 3)
        return false;

    pcur += tmp;

    tmp = strspn(pcur, ")-");
    if (tmp != 2)
        return false;

    pcur += tmp;

    tmp = strspn(pcur, DIGITS);
    if (tmp != 3)
        return false;

    pcur += tmp;

    for (int i = 0; i < 2; ++i)
    {
        if (*pcur != '-')
            return false;
        ++pcur;

        tmp = strspn(pcur, DIGITS);
        if (tmp != 2)
            return false;

        pcur += tmp;
    }

    return true;
}

int main(void)
{
    string_t line, tel = "";

    int rc = input_line(line);
    if (rc)
        return rc;

    my_strip(tel, line, SPACE_SYMBOLS);

    if (strlen(tel) && (is_phone_number(tel)))
        printf("YES");
    else
        printf("NO");

    return EXIT_SUCCESS;
}
