#ifndef PRODUCT_H
#define PRODUCT_H

#include "my_argparse.h"
#include <inttypes.h>
#include <stdio.h>

#define BAD_FILENAME 5 // + 1
#define BAD_INPUT_FILE 7
#define READ_ERROR 8
#define WRITE_ERROR 9
#define SUBSTR_TOO_LONG 10
#define NOTHING_TO_OUTPUT 11
#define PRINT_ERROR 12
#define BAD_PRODUCT 13
#define BAD_MANUFACTURER 15
#define BAD_NAME 16

#define MAX_PRODNAME_LEN 30
#define MAX_MANUFACT_LEN 15

typedef struct
{
    char name[MAX_PRODNAME_LEN + 1];
    char manufacturer[MAX_MANUFACT_LEN + 1];
    uint32_t price;
    uint32_t amount;
} product_s;

int prod_comparator(product_s const *p1, product_s const *p2);
int sort_products_in_file(args_s *args);
int get_element_by_index(FILE *f, size_t index, product_s *dst);
int put_element_by_index(FILE *f, size_t index, product_s buf);
size_t prods_in_file(FILE *f);
int filesize(FILE *f);
int print_products_from_file(args_s *args);
int print_product(product_s *prod);
int add_product_to_file(args_s *args);
int scan_product(product_s *prod);
int init_product(product_s *prod);

#endif
