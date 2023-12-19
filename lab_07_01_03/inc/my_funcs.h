#ifndef MY_FUNCS
#define MY_FUNCS

#include "my_dynamic_arr.h"
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#include <assert.h>
#endif

#ifndef NUM_TYPE
#define NUM_TYPE int
// определяю, чтобы IDE не ругалась и работала тестирующая система
#endif

#ifndef SCN_FORMAT
#define SCN_FORMAT "d"
#endif

#ifndef PRI_FORMAT
#define PRI_FORMAT "d"
#endif

enum sort_errors
{
    SWAP_NULL_PTR = 1,
    SORT_NULL_PTR,
};

// сущности должны иметь одинаковый тип tested
int swap(void *pl, void *pr, size_t size);

// сортировка методом выбора (определил вариант по кольцу)
// tested
void mysort(void *base, size_t num, size_t size,
int (*compare)(const void *, const void *));

// tested
int int_cmp(const void *pl, const void *pr);

enum file_read_errors
{
    FSCANF_ERROR = 1,
    NO_ELEMENTS,
};

// tested in func_tests
int count_numbers_in_file(FILE *file, size_t *dst);
int fill_dyn_arr_from_file(my_dyn_arr_t *dst, FILE *file);

enum print_errors
{
    NOTHING_TO_OUTPUT = 1,
    FPRINTF_ERROR,
};
// tested in func_tests
int fprint_dyn_arr(my_dyn_arr_t *src, FILE *file);

enum key_errors
{
    NO_MEMORY = 1,
    EMPTY_ARRAY,
    BAD_SRC_PTRS,
};
// tested
// clang-format off
int key(const NUM_TYPE *pb_src, const NUM_TYPE *pe_src, NUM_TYPE **pb_dst,
        NUM_TYPE **pe_dst);
// clang-format on

#endif
