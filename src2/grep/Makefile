CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

OS = $(shell uname)

ifeq ($(OS), Linux)
	LINUX_LIBS=-D_GNU_SOURCE
endif

.PHONY: all clean test s21_grep

all: s21_grep test clean

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -g -lpcre $(LINUX_LIBS) -o s21_grep

test: s21_grep
	./t_grep.sh

clean:
	rm -rf *.o

style:
	clang-format --Werror -n --style=Google *.c
