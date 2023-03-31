#!/bin/bash

gcc *.c \
-Wall -Werror -Wpedantic -Wextra -Wvla \
-std=c99 -Og -g3 -lm \
-fprofile-arcs -ftest-coverage \
-o app.exe
