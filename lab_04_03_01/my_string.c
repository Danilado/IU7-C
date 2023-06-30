#include "my_string.h"

int my_split(word_t dst[], string_t src, char *seps)
{
    int word_count = 0;
    char *token = strtok(src, seps);

    while (token != NULL)
    {
        if (strlen(token) > MAX_WORD_LEN || !strlen(token))
            return -1;
        strncpy(dst[word_count], token, strlen(token) + 1);
        ++word_count;
        token = strtok(NULL, seps);
    }

    return word_count;
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
