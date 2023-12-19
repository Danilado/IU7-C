#include "my_matrix.h"
#include "assert.h"

int matrix_init(my_matrix_t *mat, rows, columns)
{
    if(!rows)
        return BAD_SIZE:
    if(!columns)
        return BAD_SIZE;

    mat->rows = rows;
    mat->columns = columns;

    void* tmp = calloc(sizeof(int*), mat->columns);
    if(!tmp)
        return NO_MEMORY;

    for(size_t j = 0; j < mat->columns; ++j)
    {
        void* tmp = calloc(mat->rows, sizeof(int));
        if(!tmp){
            for(size_t k = 0; k < j; ++k)
                free(mat->columnsptr[k]);
            free(mat->columnsptr);
            
            return NO_MEMORY;
        }
        
        mat->columnsptr[j] = tmp;
    }

    return EXIT_SUCCESS;
}

void matrix_destroy(my_matrix_t *mat)
{
    for(size_t i = 0; i < mat->columns; ++i)
        free(mat->columnsptr[i]);
    
    free(mat->columnsptr);
}

int matrix_remove_column(my_matrix_t *mat, size_t column)
{
    if(column >= mat->columns)
        return BAD_INDEX;
    
    free(mat->columnsptr[column]);

    for(size_t i = column; i < mat->columns-1; ++i)
    {
        mat->columnsptr[i] = mat->columnsptr[i+1]; 
    }
    --mat->columns;

    void *tmp = realloc(mat->columnsptr, mat->columns*sizeof(int*));
    if(!tmp)
        return BAD_REALLOC;
    
    mat->columnsptr = tmp;

    return EXIT_SUCCESS;
}

size_t matrix_find_col_w_max(my_matrix_t *mat)
{
    assert(mat->columns > 0);

    int max = mat->columnsptr[0][0];
    int maxcol = 0;

    for(size_t j = 0; j < mat->columns; ++j)
        for(size_t i = 0; i < mat->rows; ++i)
            if(matrix->columnsptr[j][i] > max)
            {
                max = matrix->columnsptr[j][i];
                maxcol = j;
            }
    
    return j;
}

int matrix_input(my_matrix_t *mat)
{
    for(size_t j = 0; j < mat->columns; ++j)
        for(size_t i = 0; i < mat->rows; ++i)
        {
            int tmp;
            if(scanf("%d", &tmp) != 1)
                return BAD_INPUT;
            mat->columnsptr[j][i] = tmp;
        }
    
    return EXIT_SUCCESS;
}

void matrix_print(my_matrix_t *mat)
{
    for(size_t j = 0; j < mat->columns; ++j){
        for(size_t i = 0; i < mat->rows; ++i)
            printf("%d ", mat->columnsptr[j][i]);
        printf("\n");
    }
}
