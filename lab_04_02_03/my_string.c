#include "my_string.h"

int my_split(word_t dst[], string_t src, char *seps)
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
