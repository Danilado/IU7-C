#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 256

char *my_strpbrk(const char *s1, const char *s2);
size_t my_strspn(const char *s1, const char *s2);
size_t my_strcspn(const char *s1, const char *s2);
char *my_strchr(const char *s, int c);
char *my_strrchr(const char *s, int c);

typedef char string_t[MAX_STR_LEN + 1];

#endif
