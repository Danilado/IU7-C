#!/bin/bash

clang main.c matrixes.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -Og -g3 \
-fsanitize=undefined -fno-omit-frame-pointer

clang -lm -fsanitize=undefined -fno-omit-frame-pointer main.o matrixes.o -o app.exe
