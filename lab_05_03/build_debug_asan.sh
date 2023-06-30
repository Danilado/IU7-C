#!/bin/bash

clang main.c int32_file.c my_args.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=address -fno-omit-frame-pointer

clang -lm -fsanitize=address main.o int32_file.o my_args.o -o app.exe
