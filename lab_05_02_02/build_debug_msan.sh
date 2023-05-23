#!/bin/bash

clang main.c file.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -c -O0 -g3 \
-fsanitize=memory -fPIE -fno-omit-frame-pointer

clang -lm -fsanitize=memory -fPIE -fno-omit-frame-pointer main.o file.o -o app.exe
