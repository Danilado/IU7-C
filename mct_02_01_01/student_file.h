#ifndef STUDENT_FILE_H
#define STUDENT_FILE_H

#define BAD_FILENAME 3

#include "student.h"
#include <stdio.h>
#include <stdlib.h>

size_t get_student_amount(FILE *f);
size_t print_students_from_file(const char *filename);
int add_student_to_file(const char *filename, student_s *s);
int remove_students_by_attr(const char *filename);

#endif
