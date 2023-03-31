#!/bin/bash

for FILE in *.c; do
  gcc "$FILE" \
  -Wall -Werror -Wpedantic -Wextra -Wvla \
  -std=c99 -c -O3 \
  -o "${FILE%.c}.o"
done

gcc -lm ./*.o -o app.exe
