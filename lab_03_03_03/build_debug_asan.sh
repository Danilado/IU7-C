#!/bin/bash

clang main.c matrixes.c arrays.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -Og -g3 \
-fsanitize=address -fno-omit-frame-pointer

clang -lm -fsanitize=address -fno-omit-frame-pointer main.o matrixes.o arrays.o -o app.exe
