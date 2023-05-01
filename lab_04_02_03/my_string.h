#ifndef MY_STRING
#define MY_STRING

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16

typedef char string[MAX_STR_LEN + 1];
typedef char word[MAX_WORD_LEN + 1];

int my_split(word dst[], string src, char *sep);

#endif
