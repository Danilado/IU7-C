#include "my_string.h"

char *my_strpbrk(const char *s1, const char *s2)
{
    for (char *pcur = (char *)s1; *pcur != '\0'; ++pcur)
        for (char *scur = (char *)s2; *scur != '\0'; ++scur)
            if (*pcur == *scur)
                return pcur;

    return NULL;
}

size_t my_strspn(const char *s1, const char *s2)
{
    size_t ans = 0;

    for (char *pcur = (char *)s1; *pcur != '\0'; ++pcur)
    {
        bool sub_found = false;
        for (char *scur = (char *)s2; *scur != '\0'; ++scur)
            if (*pcur == *scur)
            {
                sub_found = true;
                break;
            }

        if (sub_found)
            ++ans;
        else
            return ans;
    }

    return ans;
}

size_t my_strcspn(const char *s1, const char *s2)
{
    size_t ans = 0;

    for (char *pcur = (char *)s1; *pcur != '\0'; ++pcur)
    {
        bool sub_found = false;
        for (char *scur = (char *)s2; *scur != '\0'; ++scur)
            if (*pcur == *scur)
            {
                sub_found = true;
                break;
            }

        if (sub_found)
            return ans;
        else
            ++ans;
    }

    return ans;
}

size_t my_strlen(const char *s)
{
    char *pcur = (char *)s;
    while (*pcur != 0)
        ++pcur;

    return pcur - s;
}

char *my_strchr(const char *s, int c)
{
    if (c == 0)
        return (char *)s + my_strlen(s);

    for (char *pcur = (char *)s; *pcur != '\0'; ++pcur)
        if (*pcur == c)
            return pcur;

    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    if (c == 0)
        return (char *)s + my_strlen(s);

    char *result_pointer = NULL;
    for (char *pcur = (char *)s; *pcur != '\0'; ++pcur)
        if (*pcur == c)
            result_pointer = pcur;

    return result_pointer;
}
