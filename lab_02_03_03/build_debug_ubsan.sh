#!/bin/bash

clang main.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=undefined -fno-omit-frame-pointer \
-o main.o

clang -lm -fsanitize=undefined -fno-omit-frame-pointer \
main.o -o app.exe
