#!/bin/bash

for FILE in *.c; do
  gcc "$FILE" \
  -Wall -Werror -Wpedantic -Wextra -Wvla \
  -std=c99 -c -Og -g3 \
  -fprofile-arcs -ftest-coverage \
  -o "${FILE%.c}.o"
done

gcc -lm -fprofile-arcs -lgcov ./*.o -o app.exe
