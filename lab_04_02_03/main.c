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
#define LINE_TOO_LONG_ERROR 4
#define NOTHING_TO_OUTPUT_ERROR 5
// к следующей константе прибавляется до LINES_TO_INPUT - 1
// в зависимости от строки (не кода), в которой возникла ошибка
#define WORD_TOO_LONG_ERROR 6

size_t count_occurances(word w, word arr[], size_t alen)
{
    size_t counter = 0;
    for (size_t i = 0; i < alen; ++i)
        if (strcmp(w, arr[i]) == 0)
            ++counter;

    return counter;
}

int input_line(string dst)
{
    char tmp_string[MAX_STR_LEN + 2];

    if (fgets(tmp_string, MAX_STR_LEN + 2, stdin) == NULL)
        return LINE_INPUT_ERROR;

    tmp_string[strcspn(tmp_string, "\n")] = '\0';

    if (strlen(tmp_string) && (strlen(tmp_string) - 1 > MAX_STR_LEN))
        return LINE_TOO_LONG_ERROR;

    strncpy(dst, tmp_string, MAX_STR_LEN + 1);

    return 0;
}

size_t filter_unique(word dst[], word src[][MAX_STR_LEN / 2], size_t srclens[])
{
    size_t dstlen = 0;

    for (size_t i = 0; i < LINES_TO_INPUT; ++i)
        for (size_t j = 0; j < srclens[i]; ++j)
        {
            size_t occurances = 0;
            for (size_t k = 0; k < LINES_TO_INPUT; ++k)
                occurances += count_occurances(src[i][j], src[k], srclens[k]);
            if (occurances == 1)
            {
                strncpy(dst[dstlen], src[i][j], strlen(src[i][j]));
                dst[dstlen][strlen(src[i][j])] = '\0';
                ++dstlen;
            }
        }

    return dstlen;
}

int main(void)
{
    size_t line_count;
    char sep_symbol_saver;

    if (scanf("%zu", &line_count) != 1)
        return LINE_COUNT_INPUT_ERROR;

    scanf("%c", &sep_symbol_saver);

    if (line_count != LINES_TO_INPUT)
        return LINE_COUNT_ERROR;

    string lines[LINES_TO_INPUT];

    for (size_t i = 0; i < line_count; ++i)
    {
        int rc = input_line(lines[i]);
        if (rc)
            return rc;
    }

    word words_in_lines[LINES_TO_INPUT][MAX_STR_LEN / 2];
    size_t wlens[LINES_TO_INPUT];

    for (size_t i = 0; i < line_count; ++i)
    {
        int word_count;
        word_count = my_split(words_in_lines[i], lines[i], SEPS);

        if (word_count < 0)
            return WORD_TOO_LONG_ERROR + i;

        wlens[i] = word_count;
    }

    word unique_words[LINES_TO_INPUT * MAX_STR_LEN / 2];
    size_t ans_len = 0;

    ans_len = filter_unique(unique_words, words_in_lines, wlens);

    if (!ans_len)
        return NOTHING_TO_OUTPUT_ERROR;

    printf("Result: ");

    for (size_t i = 0; i < ans_len; ++i)
        printf("%s ", unique_words[i]);

    printf("\n");

    return EXIT_SUCCESS;
}
