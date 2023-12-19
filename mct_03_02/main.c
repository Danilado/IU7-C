// дин матрица
// удалить столбец с макс. элементом

#include "my_matrix.h"
#include <stdio.h>

int main(void)
{
    my_matrix_t mat;
    long n, m;
    int rc;

    if(scanf("%ld", &n) != 1 || n <= 0)
        return BAD_SIZE;
    if(scanf("%ld", &m) != 1 || m <= 0)
        return BAD_SIZE;

    rc = matrix_init(&mat, n, m);
    if(rc)
        return rc;
    
    rc = matrix_input(&mat);
    if(rc){
        matrix_destroy(&mat);
        return rc;
    }
    
    puts("Вы ввели:");
    matrix_print(&mat);

    rc = matrix_remove_column(&mat, matrix_find_col_w_max(&mat));
    if(rc){
        matrix_destroy(&mat);
        return rc;
    }
    puts("Результат:");
    matrix_print(&mat);

    matrix_destroy(&mat);

    return EXIT_SUCCESS;
}
