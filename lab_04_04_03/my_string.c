#include "my_string.h"

int my_strip(string_t dst, string_t src, char *seps)
{
    char *token = strtok(src, seps);

    if (token == NULL || !strlen(token))
        return 1;

    strncpy(dst, token, strlen(token) + 1);

    return 0;
}
