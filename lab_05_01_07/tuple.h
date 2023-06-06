#ifndef TUPLE
#define TUPLE

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int prev;
    int cur;
    int next;
    int filled_els;
} tuple;

int push_into_tuple(tuple *t, int value);
int init_tuple(tuple *t);

#endif
