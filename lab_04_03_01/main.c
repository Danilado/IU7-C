#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPS " ,;:-.!?"

#define LINE_INPUT_ERROR 1
#define LINE_TOO_LONG_ERROR 2
#define WORD_TOO_LONG_ERROR 3
#define TOO_FEW_WORDS_ERROR 4
#define NOTHING_TO_OUTPUT_ERROR 5

void remove_dub_chars(word_t word)
{
    word_t tmp = "";
    for (char *pcur = word; *pcur != '\0'; ++pcur)
        if (strspn(pcur, tmp) == 0)
            strncat(tmp, pcur, 1);

    strncpy(word, tmp, MAX_WORD_LEN + 1);
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
        return TOO_FEW_WORDS_ERROR;

    for (int i = wlen - 2; i >= 0; --i)
    {
        if (strcmp(words[i], words[wlen - 1]) == 0)
            continue;

        remove_dub_chars(words[i]);

        strncat(ans, " ", MAX_WORD_LEN + 1);
        strncat(ans, words[i], MAX_WORD_LEN + 1);
    }

    if (!strlen(ans))
        return NOTHING_TO_OUTPUT_ERROR;

    printf("Result:%s\n", ans);

    return EXIT_SUCCESS;
}
