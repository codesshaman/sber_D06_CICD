#!/bin/bash

cp materials/linters/.clang-format src/

clang-format -n -Werror -i src/*/*.c
if [[ $? -eq 0 ]]
then
  exit 0
else
  exit 1
fi
