#!/bin/bash

clang main.c \
-Wall -Werror -Wpedantic -Wextra \
-std=c99 -c -Og -g3 \
-fsanitize=memory -fPIE -fno-omit-frame-pointer \
-o main.o

clang -lm -fsanitize=memory -fPIE main.o -o app.exe
