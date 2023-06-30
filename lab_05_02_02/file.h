#ifndef FILE_H
#define FILE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_INPUT 1
#define NOT_ENOUGH_INPUT 2

int avg_from_file(FILE *f, double *dst);
int variance_from_file(FILE *f, double *dst);

#endif
