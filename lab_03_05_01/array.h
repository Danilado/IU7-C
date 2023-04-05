#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>

#define NMAX 100

typedef int arr_t[NMAX];

#endif

void arr_shift_left(arr_t arr, size_t alen, int amount);
