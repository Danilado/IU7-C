#include "my_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES_TO_INPUT 2
#define SEPS ",;:-.!?"

#define LINE_COUNT_INPUT_ERROR 1
#define LINE_COUNT_ERROR 2
#define LINE_INPUT_ERROR 3
#define WORD_TOO_LONG_ERROR 4
#define NOTHING_TO_OUTPUT_ERROR 5
// к следующей константе прибавляется до LINES_TO_INPUT - 1
// в зависимости от строки (не кода), в которой возникла ошибка
#define LINE_TOO_LONG_ERROR 6

bool is_unique(word w, word arr[], size_t alen)
{
    int counter = 0;
    for (size_t i = 0; i < alen; ++i)
        if (strcmp(w, arr[i]) == 0)
            ++counter;

    return counter == 1;
}

int input_line(string dst)
{
    char tmp_string[MAX_STR_LEN + 2];
    if (fgets(tmp_string, MAX_STR_LEN + 2, stdin) == NULL)
        return LINE_INPUT_ERROR;
    if (strlen(tmp_string) > MAX_STR_LEN)
        return LINE_TOO_LONG_ERROR;
    strncpy(dst, tmp_string, MAX_STR_LEN);
    return 0;
}

size_t filter_unique(word dst[], word src[], size_t srclen)
{
    size_t dstlen = 0;

    for (size_t i = 0; i < srclen; ++i)
        if (is_unique(src[i], src, srclen))
        {
            strncpy(dst[dstlen], src[i], strlen(src[i]));
            ++dstlen;
        }

    return dstlen;
}

int main(void)
{
    size_t line_count;

    if (scanf("%zu", &line_count) != 1)
        return LINE_COUNT_INPUT_ERROR;

    if (line_count != LINES_TO_INPUT)
        return LINE_COUNT_ERROR;

    string lines[LINES_TO_INPUT];

    for (size_t i = 0; i < line_count; ++i)
    {
        int rc = input_line(lines[i]);
        if (rc)
            return rc;
    }

    word words[LINES_TO_INPUT * MAX_STR_LEN / 2];
    size_t wlen = 0;

    for (size_t i = 0; i < line_count; ++i)
    {
        int word_count;
        word_count = my_split(words + wlen, lines[i], SEPS);

        if (word_count < 0)
            return WORD_TOO_LONG_ERROR + i;

        wlen += word_count;
    }

    word unique_words[LINES_TO_INPUT * MAX_STR_LEN / 2];
    size_t ans_len = 0;

    ans_len = filter_unique(unique_words, words, wlen);

    if (!ans_len)
        return NOTHING_TO_OUTPUT_ERROR;

    printf("Result: ");

    for (size_t i = 0; i < ans_len; ++i)
        printf("%s ", unique_words[i]);

    return EXIT_SUCCESS;
}
