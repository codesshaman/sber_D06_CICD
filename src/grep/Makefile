CC = gcc
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	FLAGS := -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE
else
	FLAGS := -Wall -Werror -Wextra -std=c11
endif

all: clean test

s21_grep: s21_grep.c
	@$(CC) $(FLAGS) s21_grep.c -o s21_grep

test: s21_grep
	sh test_grep.sh

check:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extension=c *.c *.h

clean:
	@rm -rf *.o *.gc* *log* s21_grep

.PHONY: all test clean s21_grep