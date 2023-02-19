#!/bin/bash

bash ./clean.sh

echo DEBUG BUILD
bash ./build_debug.sh
bash ./func_tests/scripts/func_tests.sh
echo
echo COLLECT COVERAGE
bash ./collect_coverage.sh
echo

bash ./clean.sh

echo ADDRESS SANITIZER
bash ./build_debug_asan.sh
bash ./func_tests/scripts/func_tests.sh
echo

bash ./clean.sh

echo MEMORY SANITIZER
bash ./build_debug_msan.sh
bash ./func_tests/scripts/func_tests.sh
echo

bash ./clean.sh

echo UB SANITIZER
bash ./build_debug_ubsan.sh
bash ./func_tests/scripts/func_tests.sh
echo

bash ./clean.sh
