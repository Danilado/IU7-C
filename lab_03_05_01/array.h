#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

#define NMAX 100

typedef int arr_t[NMAX];

void arr_shift_left(arr_t arr, size_t alen, int amount);

#endif
