#!/bin/bash

clang main.c product.c my_argparse.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=undefined -fno-omit-frame-pointer

clang -lm -fsanitize=undefined -fno-omit-frame-pointer \
main.o product.o my_argparse.o -o app.exe
