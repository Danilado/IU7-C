#include "my_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_SYMBOLS " \t"
#define DIGITS "0123456789"

#define LINE_INPUT_ERROR 1
#define LINE_TOO_LONG_ERROR 2
#define EMPTY_STRING_ERROR 3

int input_line(string_t dst)
{
    char tmp_string[MAX_STR_LEN + 2];

    if (fgets(tmp_string, MAX_STR_LEN + 2, stdin) == NULL)
        return LINE_INPUT_ERROR;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) && (strlen(tmp_string) > MAX_STR_LEN))
        return LINE_TOO_LONG_ERROR;

    strncpy(dst, tmp_string, MAX_STR_LEN + 1);

    return 0;
}

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
    string_t line, tel;

    int rc = input_line(line);
    if (rc)
        return rc;

    rc = my_strip(tel, line, SPACE_SYMBOLS);
    if (rc)
        return EMPTY_STRING_ERROR;

    if (is_phone_number(tel))
        printf("YES");
    else
        printf("NO");

    return EXIT_SUCCESS;
}
