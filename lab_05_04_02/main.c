// (c) Добавление информации о новом товаре в уже упорядоченную последо-
// вательность товаров так, чтобы упорядоченность не нарушилась. Инфор-
// мация о новом товаре запрашивается у пользователя. Результат записы-
// вается в тот же файл. Повторное использование сортировки не считается
// правильным решением задачи.

#include "my_argparse.h"
#include "product.h"
#include <stdlib.h>

#define BAD_ARGS 53

int main(int argc, char **argv)
{
    args_s args;
    int rc;

    rc = my_argparse(argc, argv, &args);
    if (rc)
        return BAD_ARGS;

    // clang-format off
    switch (args.mode)
    {
        case SORT_MODE_CODE:
            rc = sort_products_in_file(&args);
            
            if(rc)
                return rc;
            break;
        case PRINT_MODE_CODE:
            rc = print_products_from_file(&args);
            
            if(rc > 0)
                return rc;
            
            if(rc == 0)
                return NOTHING_TO_OUTPUT;
            break;
        case ADD_MODE_CODE:
            rc = add_product_to_file(&args);
            
            if(rc)
                return rc;
            break;
    }
    // clang-format on

    return EXIT_SUCCESS;
}
