#!/bin/bash

cmd="./app.exe $1"

if $cmd>/dev/null; then
  exit 1
fi

exit 0
