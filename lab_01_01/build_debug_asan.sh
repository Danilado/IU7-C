#!/bin/bash

clang -Wall -Werror -Wpedantic -Wextra -std=c99 -c -Og -fsanitize=address -fno-omit-frame-pointer -g main.c
clang -lm -fsanitize=address main.o -o app.exe
