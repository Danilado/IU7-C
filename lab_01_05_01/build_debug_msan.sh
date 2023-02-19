#!/bin/bash

clang -Wall -Werror -Wpedantic -Wextra -std=c99 -c -Og -fsanitize=memory -fPIE -fno-omit-frame-pointer -g main.c
clang -lm -fsanitize=memory -fPIE main.o -o app.exe
