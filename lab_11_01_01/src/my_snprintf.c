#include "my_snprintf.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage" // Просто варнинг
#pragma clang diagnostic ignored "-Wdeclaration-after-statement" // У нас C99
// Ругается на size_t при обращении к массиву через квадратные скобки
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

static size_t digits_in_num(int d)
{
    if (!d)
        return 1;

    size_t res = 0;
    while (d)
    {
        ++res;
        d /= 10;
    }
    return res;
}

static size_t num_snprint(char *dst, size_t max_len, int d)
{
    size_t cur = 0;
    size_t numlen = digits_in_num(d);

    int divisor = 1;
    for (size_t i = 1; i < numlen; ++i)
        divisor *= 10;

    if (!dst)
        return numlen + ((d < 0) ? 1 : 0);

    if (d < 0 && cur < max_len)
    {
        dst[cur] = '-';
        ++cur;
    }

    while (divisor && (cur < max_len))
    {
        dst[cur] = '0' + (char)(d / divisor) * ((d < 0) ? -1 : 1);
        d %= divisor;
        divisor /= 10;
        ++cur;
    }

    return numlen + ((d < 0 || dst[0] == '-') ? 1 : 0);
}

static size_t my_strlen(const char *s)
{
    if (!s)
        return 0;

    size_t len = 0;
    const char *cur = s;
    while (*cur)
    {
        ++len;
        ++cur;
    }

    return len;
}

static void my_strncat(char *restrict dst, const char *restrict src, size_t n)
{
    char *dstlast = dst;
    while (*dstlast)
        ++dstlast;

    const char *srccur = src;

    for (size_t count = 0; count < n && *srccur; ++count)
    {
        *dstlast = *srccur;
        ++dstlast;
        ++srccur;
    }

    *dstlast = '\0';
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    size_t cur_len = 0;

    if (!format || !my_strlen(format))
    {
        if (s)
            s[0] = '\0';
        return cur_len;
    }

    va_list args;
    va_start(args, format);

    for (const char *cur = &format[0]; *cur != '\0'; ++cur)
    {
        if (*cur != '%')
        {
            if (cur_len + 1 < n && s != NULL)
                s[cur_len] = *cur;
            ++cur_len;
            continue;
        }

        ++cur;
        if (*cur == 'd')
        {
            int num = va_arg(args, int);
            if (cur_len + 1 < n)
            {
                size_t numlen = num_snprint(&s[cur_len], n - cur_len - 1, num);
                cur_len += numlen;
            }
            else
                cur_len += num_snprint(NULL, 0, num);
            continue;
        }
        if (*cur == 's')
        {
            char *pstr = va_arg(args, char *);
            if (!pstr)
                continue;

            if (cur_len + 1 < n && s != NULL)
            {
                s[cur_len] = '\0';
                my_strncat(s, pstr, n - cur_len - 1);
            }
            cur_len += my_strlen(pstr);
            continue;
        }
        if (*cur == '%')
        {
            if (cur_len + 1 < n && s != NULL)
                s[cur_len] = *cur;
            ++cur_len;
            continue;
        }

        va_end(args);
        return -UNSUPPORTED_FORMAT;
    }

    if (s != NULL)
    {
        if (cur_len + 1 < n)
            s[cur_len] = '\0';
        else
            s[n - 1] = '\0';
    }

    va_end(args);
    return cur_len;
}

#pragma clang diagnostic pop
