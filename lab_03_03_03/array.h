#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>

#define NMAX 10

typedef int arr_t[NMAX];

#endif

void arr_fill(arr_t dst, size_t num);
