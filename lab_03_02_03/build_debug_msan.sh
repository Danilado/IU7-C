#!/bin/bash

clang main.c matrix.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -Og -g3 \
-fsanitize=memory -fPIE -fno-omit-frame-pointer

clang -lm -fsanitize=memory -fPIE -fno-omit-frame-pointer main.o matrix.o -o app.exe
