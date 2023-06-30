#include "my_string.h"

void my_strip(string_t dst, string_t src, char *seps)
{
    char *token = strtok(src, seps);
    if (token != NULL)
        strncpy(dst, token, strlen(token) + 1);
}

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
