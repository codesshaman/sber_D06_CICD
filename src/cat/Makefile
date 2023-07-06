CC = gcc
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	FLAGS := -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE
else
	FLAGS := -Wall -Werror -Wextra -std=c11
endif

all: clean test

s21_cat: s21_cat.c
	@$(CC) $(FLAGS) s21_cat.c -o s21_cat

test: s21_cat
	sh t_cat.sh

check:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extension=c *.c *.h

clean:
	@rm -rf *.o *.gc* *log* s21_cat

.PHONY: all test clean s21_cat