#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPS " ,;:-.!?"

#define WORD_TOO_LONG_ERROR 3
#define NOT_ENOUGH_WORDS_ERROR 4
#define NOTHING_TO_OUTPUT_ERROR 5

void remove_dub_chars(word_t word)
{
    word_t tmp = "";
    for (char *pcur = word; *pcur != '\0'; ++pcur)
        if (strspn(pcur, tmp) == 0)
            strncat(tmp, pcur, 1);

    strncpy(word, tmp, MAX_WORD_LEN + 1);
}

void form_answer(string_t ans, word_t words[], size_t wlen)
{
    for (int i = wlen - 2; i >= 0; --i)
    {
        if (strcmp(words[i], words[wlen - 1]) == 0)
            continue;

        remove_dub_chars(words[i]);

        strncat(ans, " ", MAX_WORD_LEN + 1);
        strncat(ans, words[i], MAX_WORD_LEN + 1);
    }
}

int main(void)
{
    string_t line, ans = "";

    int rc = input_line(line);
    if (rc)
        return rc;

    word_t words[MAX_STR_LEN / 2];
    int wlen = my_split(words, line, SEPS);

    if (wlen < 0)
        return WORD_TOO_LONG_ERROR;

    if (wlen < 2)
        return NOT_ENOUGH_WORDS_ERROR;

    form_answer(ans, words, wlen);

    if (!strlen(ans))
        return NOTHING_TO_OUTPUT_ERROR;

    printf("Result:%s\n", ans);

    return EXIT_SUCCESS;
}
