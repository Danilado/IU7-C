#!/bin/bash

clang -Wall -Werror -Wpedantic -Wextra -std=c99 -c -Og -g3 -fsanitize=memory -fPIE -fno-omit-frame-pointer main.c
clang -lm -fsanitize=memory -fPIE main.o -o app.exe
