#include "my_argparse.h"
#include "my_dynamic_arr.h"
#include <stdio.h>
#include <stdlib.h>

// ДИСКЛЕЙМЕР
// Я тут пытался сделать что-то когерентное, чтобы оно могло работать с любыми
// типами данных. Я понимаю, что по заданию у нас только int, что видно из
// прототифа функции-фильтра key. Я сделал её как по заданию, однако
// такой вариант кода должно быть не сложно переписать под любой тип данных

// чисто теоретически, так можно заменить int на любой числовой формат
#define NUM_TYPE int
#define SCN_FORMAT "d" // два макроса для вещественных чисел
#define PRI_FORMAT "d" // там точность на выводе, все дела
#include "my_funcs.h"

enum error_classes
{
    ERROR_IN_ARGPARSE = 0,
    SCAN_ERROR = 10,
    DYN_ARR_ERROR = 20,
    PROCESSING_ERROR = 30,
    PRINT_ERROR = 40,
};

int main(int argc, char **argv)
{
    int rc;

    args_t args;
    rc = my_argparse(argc, argv, &args);
    if (rc)
        return ERROR_IN_ARGPARSE + rc;

    size_t number_count;
    rc = count_numbers_in_file(args.file_in, &number_count);
    if (rc)
    {
        fclose(args.file_in);
        fclose(args.file_out);
        return SCAN_ERROR + rc;
    }

    my_dyn_arr_t arr;
    rc = dyn_arr_init(sizeof(NUM_TYPE), number_count, &arr);
    if (rc)
    {
        fclose(args.file_in);
        fclose(args.file_out);
        return DYN_ARR_ERROR + rc;
    }

    rc = fill_dyn_arr_from_file(&arr, args.file_in);

    fclose(args.file_in);

    if (rc)
    {
        dyn_arr_destroy(&arr);
        fclose(args.file_out);
        return PROCESSING_ERROR + rc;
    }

    if (args.filter)
    {
        my_dyn_arr_t tmp;
        tmp.el_size = arr.el_size;

        rc = key(arr.pb, arr.pe, (NUM_TYPE **)&tmp.pb, (NUM_TYPE **)&tmp.pe);
        if (rc)
        {
            dyn_arr_destroy(&arr);
            fclose(args.file_out);
            return PROCESSING_ERROR + rc;
        }

        dyn_arr_destroy(&arr);
        arr = tmp;
    }

    number_count = ((char *)arr.pe - (char *)arr.pb) / arr.el_size;

    mysort(arr.pb, number_count, arr.el_size, int_cmp);

    rc = fprint_dyn_arr(&arr, args.file_out);

    fclose(args.file_out);
    dyn_arr_destroy(&arr); // free внутри

    if (rc)
        return PRINT_ERROR + rc;

    return EXIT_SUCCESS;
}
