#!/bin/bash

clang -Wall -Werror -Wpedantic -Wextra -std=c99 -c -Og -fsanitize=undefined -fno-omit-frame-pointer -g main.c
clang -lm -fsanitize=undefined -fno-omit-frame-pointer main.o -o app.exe
