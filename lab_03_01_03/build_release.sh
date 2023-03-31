#!/bin/bash

gcc *.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -O3 -lm \
-o app.exe
