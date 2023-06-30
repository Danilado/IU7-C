#ifndef INT32_FILE_H
#define INT32_FILE_H

#include "my_args.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BAD_FILENAME 4
#define WRITE_ERROR 7
#define READ_ERROR 8

size_t get_element_amount(FILE *f);
int get_element_by_index(FILE *f, size_t index, int32_t *dst);
int put_element_by_index(FILE *f, size_t index, int32_t buf);

int create_file(args_s *args);
int print_file(args_s *args);
int sort_file(args_s *args);

#endif
