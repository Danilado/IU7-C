#!/bin/bash

clang *.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -Og -g3 -lm \
-fsanitize=address -fno-omit-frame-pointer \
-o app.exe
