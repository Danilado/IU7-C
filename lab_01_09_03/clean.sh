#!/bin/bash

tmpfiles="*.exe *.o *.gcov *.gcno *.gcda out.txt"

for FILE in $tmpfiles; do
  rm -f "$FILE"
done

exit 0
