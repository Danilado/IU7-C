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
