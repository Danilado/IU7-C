#!/bin/bash

clang main.c my_string.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O3

clang -lm main.o my_string.o -o app.exe
