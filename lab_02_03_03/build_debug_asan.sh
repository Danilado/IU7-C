#!/bin/bash

clang main.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=address -fno-omit-frame-pointer \
-o main.o

clang -lm -fsanitize=address main.o -o app.exe
