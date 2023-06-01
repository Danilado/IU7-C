#!/bin/bash

gcc main.c product.c my_argparse.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fprofile-arcs -ftest-coverage

gcc -lm -fprofile-arcs -lgcov main.o product.o my_argparse.o -o app.exe
