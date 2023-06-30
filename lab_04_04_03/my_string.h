#ifndef MY_STRING_H
#define MY_STRING_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16

#define LINE_INPUT_ERROR 1
#define LINE_TOO_LONG_ERROR 2

typedef char string_t[MAX_STR_LEN + 1];
typedef char word_t[MAX_WORD_LEN + 1];

int input_line(string_t dst);
void my_strip(string_t dst, string_t src, char *sep);

#endif
