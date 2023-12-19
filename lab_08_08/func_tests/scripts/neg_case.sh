#!/bin/bash

cmd="valgrind -q --leak-check=full ./app.exe"

if $cmd<"$1">/dev/null; then
  exit 1
fi

exit 0
