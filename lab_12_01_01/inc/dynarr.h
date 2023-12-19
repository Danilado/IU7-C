#ifndef DYNARR_H
#define DYNARR_H

// ДИСКЛЕЙМЕР
// Я тут пытался сделать что-то когерентное, чтобы оно могло работать с любыми
// типами данных. Я понимаю, что по заданию у нас только int, что видно из
// прототифа функции-фильтра key. Я сделал её как по заданию, однако
// такой вариант кода должно быть не сложно переписать под любой тип данных
// чисто теоретически, так можно заменить int на любой числовой формат
// !!! Не будет работать ни с чем кроме инта при линковке через ldl
#define NUM_TYPE int
#define SCN_FORMAT "d" // два макроса для вещественных чисел
#define PRI_FORMAT "d" // там точность на выводе, все дела

#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct my_dyn_arr
{
    void *pb;
    void *pe;
    size_t el_size;
} my_dyn_arr_t;

enum dyn_arr_errors
{
    NOT_ENOUGH_MEMORY = 1,
};

enum print_errors
{
    NOTHING_TO_OUTPUT = 1,
    FPRINTF_ERROR,
};

int dyn_arr_init(size_t el_size, size_t el_count, my_dyn_arr_t *dst);
void dyn_arr_destroy(my_dyn_arr_t *arr);

// tested in func_tests
int fill_dyn_arr_from_file(my_dyn_arr_t *dst, FILE *file);
int fprint_dyn_arr(my_dyn_arr_t *src, FILE *file);

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

enum key_errors
{
    NO_MEMORY = 1,
    EMPTY_ARRAY,
    BAD_SRC_PTRS,
    BAD_DST_PTRS,
};
// tested
// clang-format off
int key(const NUM_TYPE *pb_src, const NUM_TYPE *pe_src, NUM_TYPE **pb_dst,
        NUM_TYPE **pe_dst);
// clang-format on

#endif
