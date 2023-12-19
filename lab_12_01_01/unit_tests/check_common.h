#ifndef CK_COMMON_H
#define CK_COMMON_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_TYPE int

typedef struct my_dyn_arr {
  void *pb;
  void *pe;
  size_t el_size;
} my_dyn_arr_t;

enum dyn_arr_errors {
  NOT_ENOUGH_MEMORY = 1,
};

enum print_errors {
  NOTHING_TO_OUTPUT = 1,
  FPRINTF_ERROR,
};

enum key_errors {
  NO_MEMORY = 1,
  EMPTY_ARRAY,
  BAD_SRC_PTRS,
  BAD_DST_PTRS,
};

typedef int (*fn_dyn_arr_init_t)(size_t, size_t, my_dyn_arr_t *);
typedef void (*fn_dyn_arr_destroy_t)(my_dyn_arr_t *);
typedef int (*fn_fill_dyn_arr_from_file_t)(my_dyn_arr_t *, FILE *);
typedef int (*fn_fprint_dyn_arr_t)(my_dyn_arr_t *, FILE *);
typedef int (*fn_swap_t)(void *, void *, size_t);
typedef void (*fn_mysort_t)(void *, size_t, size_t,
                            int (*)(const void *, const void *));
typedef int (*fn_int_cmp_t)(const void *, const void *);
typedef int (*fn_count_numbers_in_file_t)(FILE *, size_t *);
typedef int (*fn_key_t)(const int *, const int *, int **, int **);

extern void *dynarrlib;
extern fn_count_numbers_in_file_t count_numbers_in_file;
extern fn_dyn_arr_init_t dyn_arr_init;
extern fn_fill_dyn_arr_from_file_t fill_dyn_arr_from_file;
extern fn_dyn_arr_destroy_t dyn_arr_destroy;
extern fn_key_t key;
extern fn_mysort_t mysort;
extern fn_fprint_dyn_arr_t fprint_dyn_arr;
extern fn_int_cmp_t int_cmp;
extern fn_swap_t swap;

#endif
