#ifndef STUDENT_H
#define STUDENT_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#define BAD_SURNAME 1
#define BAD_HEIGHT 2

#define MAX_SURNAME_LEN 5

typedef struct student
{
    char surname[MAX_SURNAME_LEN + 1];
    int32_t height;
} student_s;

#define SIZEOFSTUDENT (sizeof(int) + sizeof(char) * (MAX_SURNAME_LEN + 1))

int print_student(student_s s);
int read_student_from_file(student_s *s, FILE *f);
int student_input(student_s *s);

#endif
