#include "my_string.h"

int my_split(word dst[], string src, char *seps)
{
    int words_len = 0;
    int cur_word_len = 0;
    for (char *pcur = src; *pcur != '\0'; ++pcur)
    {
        if (isspace(*pcur) || strspn(pcur, seps) != 0)
        {
            if (cur_word_len)
            {
                dst[words_len][cur_word_len] = '\0';
                cur_word_len = 0;
                ++words_len;
            }
            continue;
        }
        dst[words_len][cur_word_len] = *pcur;
        ++cur_word_len;

        if (cur_word_len > MAX_WORD_LEN)
            return -1;
    }

    if (cur_word_len)
    {
        dst[words_len][cur_word_len] = '\0';
        ++words_len;
    }

    return words_len;
}
