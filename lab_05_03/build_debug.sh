#!/bin/bash

gcc main.c int32_file.c my_args.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fprofile-arcs -ftest-coverage

gcc -lm -fprofile-arcs -lgcov main.o int32_file.o my_args.o -o app.exe
