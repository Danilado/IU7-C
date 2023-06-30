#include "my_string.h"
#include <stdio.h>
#include <string.h>

#define NMAX 10
#define STRPBRK_TESTS_N 7
#define STRSPN_TESTS_N 6
#define STRCSPN_TESTS_N 6
#define STRCHR_TESTS_N 5
#define STRRCHR_TESTS_N 5

int test_strpbrk(char *s1_arr[], char *s2_arr[], size_t alen)
{
    int fail_count = 0;
    string_t s1_arr_save[NMAX];
    string_t s2_arr_save[NMAX];
    for (size_t i = 0; i < alen; ++i)
    {
        strncpy(s1_arr_save[i], s1_arr[i], MAX_STR_LEN);
        strncpy(s2_arr_save[i], s2_arr[i], MAX_STR_LEN);
    }

    for (size_t i = 0; i < alen; ++i)
    {
        char *myres = my_strpbrk(s1_arr[i], s2_arr[i]);
        char *stdres = strpbrk(s1_arr[i], s2_arr[i]);

        if (myres != stdres || strcmp(s1_arr[i], s1_arr_save[i]) != 0 ||
            strcmp(s2_arr[i], s2_arr_save[i]) != 0)
        {
            ++fail_count;
            continue;
        }
    }

    return fail_count;
}

int test_strspn(char *s1_arr[], char *s2_arr[], size_t alen)
{
    int fail_count = 0;
    string_t s1_arr_save[NMAX];
    string_t s2_arr_save[NMAX];
    for (size_t i = 0; i < alen; ++i)
    {
        strncpy(s1_arr_save[i], s1_arr[i], MAX_STR_LEN);
        strncpy(s2_arr_save[i], s2_arr[i], MAX_STR_LEN);
    }

    for (size_t i = 0; i < alen; ++i)
    {
        size_t myres = my_strspn(s1_arr[i], s2_arr[i]);
        size_t stdres = strspn(s1_arr[i], s2_arr[i]);

        if (myres != stdres || strcmp(s1_arr[i], s1_arr_save[i]) != 0 ||
            strcmp(s2_arr[i], s2_arr_save[i]) != 0)
        {
            ++fail_count;
            continue;
        }
    }

    return fail_count;
}

int test_strcspn(char *s1_arr[], char *s2_arr[], size_t alen)
{
    int fail_count = 0;
    string_t s1_arr_save[NMAX];
    string_t s2_arr_save[NMAX];
    for (size_t i = 0; i < alen; ++i)
    {
        strncpy(s1_arr_save[i], s1_arr[i], MAX_STR_LEN);
        strncpy(s2_arr_save[i], s2_arr[i], MAX_STR_LEN);
    }

    for (size_t i = 0; i < alen; ++i)
    {
        size_t myres = my_strcspn(s1_arr[i], s2_arr[i]);
        size_t stdres = strcspn(s1_arr[i], s2_arr[i]);

        if (myres != stdres || strcmp(s1_arr[i], s1_arr_save[i]) != 0 ||
            strcmp(s2_arr[i], s2_arr_save[i]) != 0)
        {
            ++fail_count;
            continue;
        }
    }

    return fail_count;
}

int test_strchr(char *s_arr[], int c_arr[], size_t alen)
{
    int fail_count = 0;
    string_t s_arr_save[NMAX];
    int c_arr_save[NMAX];
    for (size_t i = 0; i < alen; ++i)
    {
        strncpy(s_arr_save[i], s_arr[i], MAX_STR_LEN);
        c_arr_save[i] = c_arr[i];
    }

    for (size_t i = 0; i < alen; ++i)
    {
        char *myres = my_strchr(s_arr[i], c_arr[i]);
        char *stdres = strchr(s_arr[i], c_arr[i]);

        if (myres != stdres || strcmp(s_arr[i], s_arr_save[i]) != 0 ||
            c_arr[i] != c_arr_save[i])
        {
            ++fail_count;
            continue;
        }
    }

    return fail_count;
}

int test_strrchr(char *s_arr[], int c_arr[], size_t alen)
{
    int fail_count = 0;
    string_t s_arr_save[NMAX];
    int c_arr_save[NMAX];
    for (size_t i = 0; i < alen; ++i)
    {
        strncpy(s_arr_save[i], s_arr[i], MAX_STR_LEN);
        c_arr_save[i] = c_arr[i];
    }

    for (size_t i = 0; i < alen; ++i)
    {
        char *myres = my_strrchr(s_arr[i], c_arr[i]);
        char *stdres = strrchr(s_arr[i], c_arr[i]);

        if (myres != stdres || strcmp(s_arr[i], s_arr_save[i]) != 0 ||
            c_arr[i] != c_arr_save[i])
        {
            ++fail_count;
            continue;
        }
    }

    return fail_count;
}

int main(void)
{
    int fail_sum = 0;

    { // strpbrk
        char *spbrk_t1[] = {
            "jwnfoibwfibiqbfplwdq",
            "mama papa ya",
            "wow a line\nbreak",
            "Я Русский!",
            "",
            "smth",
            "",
        };

        char *spbrk_t2[] = {
            "123bvn", " ", "\n", "Я иду до конца!", "fknwelfbwepidnaknpierb",
            "",       "",
        };

        int strpbrk_fails = test_strpbrk(spbrk_t1, spbrk_t2, STRPBRK_TESTS_N);
        fail_sum += strpbrk_fails;

        printf("При тестировании strpbrk возникло %d ошибок\n", strpbrk_fails);
    }

    { // strspn
        char *sspn_t1[] = {
            "qkrblbf 9lwbqf;fw mew;njgb/dpojqfpdskbcsm sc",
            "982716283056023409370938147587306",
            "Я снова Русский.",
            "skfskfj",
            "",
            "",
        };

        char *sspn_t2[] = {
            "qnwirbkfdsbj", "12345", "Это ли не прекрасно?", "", "qkjdbqd", "",
        };

        int strspn_fails = test_strspn(sspn_t1, sspn_t2, STRSPN_TESTS_N);
        fail_sum += strspn_fails;

        printf("При тестировании strspn возникло %d ошибок\n", strspn_fails);
    }

    { // strcspn
        char *scspn_t1[] = {
            "qkrblbf 9lwbqf;fw mew;njgb/dpojqfpdskbcsm sc",
            "982716283056023409370938147587306",
            "Я снова Русский.",
            "skfskfj",
            "",
            "",
        };

        char *scspn_t2[] = {
            "qnwirbkfdsbj", "12345", "Это ли не прекрасно?", "", "qkjdbqd", "",
        };

        int strcspn_fails = test_strcspn(scspn_t1, scspn_t2, STRCSPN_TESTS_N);
        fail_sum += strcspn_fails;

        printf("При тестировании strcspn возникло %d ошибок\n", strcspn_fails);
    }

    { // strchr
        char *schr_t1[] = {
            "qkrblbf 9lwbqf;fw mew;njgb/dpojqfpdskbcsm sc",
            "982716283056023409370938147587306",
            "skfskfj",
            "",
            "",
        };

        int schr_t2[] = {
            'w', '3', 'f', '1', '\0',
        };

        int strchr_fails = test_strchr(schr_t1, schr_t2, STRCHR_TESTS_N);
        fail_sum += strchr_fails;

        printf("При тестировании strchr возникло %d ошибок\n", strchr_fails);
    }

    { // strrchr
        char *srchr_t1[] = {
            "qkrblbf 9lwbqf;fw mew;njgb/dpojqfpdskbcsm sc",
            "982716283056023409370938147587306",
            "skfskfj",
            "",
            "",
        };

        int srchr_t2[] = {
            'w', '3', 'f', '1', '\0',
        };

        int strrchr_fails = test_strrchr(srchr_t1, srchr_t2, STRRCHR_TESTS_N);
        fail_sum += strrchr_fails;

        printf("При тестировании strкchr возникло %d ошибок\n", strrchr_fails);
    }

    return fail_sum;
}
