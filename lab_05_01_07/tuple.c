#include "tuple.h"

int init_tuple(tuple *t)
{
    t->filled_els = 0;
    return 0;
}

int push_into_tuple(tuple *t, int value)
{
    if (t->filled_els != 3)
    {
        if (t->filled_els == 0)
            t->prev = value;
        else if (t->filled_els == 1)
            t->cur = value;
        else
            t->next = value;
        ++t->filled_els;
        return 0;
    }

    t->prev = t->cur;
    t->cur = t->next;
    t->next = value;

    return 0;
}
