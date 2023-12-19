#!/bin/bash

#   args:
#   $1  :   ./func_tests/data/pos_"${num}"_in.txt
#   $2  :   ./func_tests/data/pos_"${num}"_out.txt
#   $3  :   ./func_tests/data/pos_"${num}"_args.txt
#   $4  :   ./func_tests/data/pos_file_"${num}"_in.bin
#   $5  :   ./func_tests/data/pos_file_"${num}"_out.bin

cmd="valgrind -q --leak-check=full ./app.exe"

# expects regular output

if ! $cmd < "$1" >./out.txt ; then
  exit 1
fi
  
if ./func_tests/scripts/comparator.sh ./out.txt "$2"; then
  exit 0
fi
  
exit 1

