CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

OS = $(shell uname)

ifeq ($(OS), Linux)
	LINUX_LIBS=-D_GNU_SOURCE
endif

.PHONY: all test clean s21_cat

all: s21_cat test clean

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c $(LINUX_LIBS) -o s21_cat

test:
	./t_cat.sh

clean:
	rm -rf *.o log.txt

style:
		clang-format --Werror -n --style=Google *.c
