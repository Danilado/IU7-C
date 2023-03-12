#!/bin/bash

for lab in ./lab_*_*; do
  
  echo "===== ${lab} ====="
  echo
  
  cd "$lab" || exit 1
  
  if [ -f "./go.sh" ]; then
    bash ./go.sh;
  fi
  
  cd ..
done
