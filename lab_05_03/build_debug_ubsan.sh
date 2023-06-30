#!/bin/bash

clang main.c int32_file.c my_args.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=undefined -fno-omit-frame-pointer

clang -lm -fsanitize=undefined -fno-omit-frame-pointer \
main.o int32_file.o my_args.o -o app.exe
