#!/bin/bash

gcc main.c int32_file.c my_args.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -O3

gcc -lm main.o int32_file.o my_args.o -o app.exe
