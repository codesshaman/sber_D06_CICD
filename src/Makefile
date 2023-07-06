CC := gcc
CFLAGS := -std=c11 -ggdb #-Wall -Werror -Wextra
C_LIBS := -lm
TST_LIBS := -lcheck -lm -lpthread

DATE_TIME := $(shell sh -c "date '+%F %T'")
PWD := $(shell pwd)
NICKNAME := $(shell pwd | awk 'BEGIN {FS="/";} { print $$3}')
SOURCES_CAT := $(wildcard cat/*.c)
SOURCES_GREP := $(wildcard grep/*.c)
SOURCES_COMMON := $(wildcard common/*.c)
SOURCES_TEST := $(wildcard test/*.c)
HEADERS_CAT := $(wildcard cat/*.h)
HEADERS_GREP := $(wildcard grep/*.h)
HEADERS_COMMON := $(wildcard common/*.h)
HEADERS_TEST := $(wildcard test/*.h)
OBJECTS := $(wildcard *.o)
LIBS := $(wildcard *.a)
BUILD_CAT := cat/s21_cat
BUILD_GREP := grep/s21_grep
BUILD_CAT_TEST := s21_cat_test
BUILD_GREP_TEST := s21_grep_test
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
	TST_LIBS+= -lcheck_pic -lrt -lsubunit
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	else
		CFLAGS+=-D LINUX
		TST_LIBS+= -lcheck_pic -lrt -lsubunit
	endif
endif

all: build

rebuild: clean build

build: s21_cat s21_grep

test: test_cat test_grep

test_cat:  test_cat.o s21_cat.o
	$(CC) $(CFLAGS) test_cat.o s21_cat.o $(TST_LIBS) -o $(BUILD_CAT_TEST)

test_cat.o: cat/s21_cat.c
	$(CC) $(CFLAGS) -c cat/s21_cat.c -o test_cat.o

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o $(BUILD_CAT)

s21_cat.o: cat/s21_cat.c
	$(CC) $(CFLAGS) -c cat/s21_cat.c -o s21_cat.o

#----------

test_grep:  test_grep.o s21_grep.o
	$(CC) $(CFLAGS) test_grep.o s21_grep.o $(TST_LIBS) -o $(BUILD_GREP_TEST)

test_grep.o: grep/s21_grep.c
	$(CC) $(CFLAGS) -c grep/s21_grep.c -o test_grep.o

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o $(BUILD_GREP)

s21_grep.o: grep/s21_grep.c
	$(CC) $(CFLAGS) -c grep/s21_grep.c -o s21_grep.o

#----------
#----------

gcov_test_cat: cat/s21_cat.c cat/s21_cat.c
	$(CC) $(CFLAGS) --coverage cat/s21_cat.c cat/s21_cat.c $(TST_LIBS) -o gcov_test_cat

gcov_test_cat.gcda: gcov_test_cat
	chmod +x ./gcov_test_cat
	./gcov_test_cat

gcov_test_cat.info: gcov_test_cat gcov_test_cat.gcda
	lcov -t "gcov_test_cat" -o gcov_test_cat.info --no-external -c -d .

report_cat: clean gcov_test_cat.info
	genhtml -o report_cat/ gcov_test_cat.info
	open report_cat/index.html

gcov_test_grep: grep/s21_grep.c grep/s21_grep.c
	$(CC) $(CFLAGS) --coverage grep/s21_grep.c grep/s21_grep.c $(TST_LIBS) -o gcov_test_grep

gcov_test_grep.gcda: gcov_test_grep
	chmod +x ./gcov_test_grep
	./gcov_test_grep

gcov_test_grep.info: gcov_test_grep gcov_test_grep.gcda
	lcov -t "gcov_test_grep" -o gcov_test_grep.info --no-external -c -d .

report_grep: clean gcov_test_grep.info
	genhtml -o report_grep/ gcov_test_grep.info
	open report_grep/index.html

#----------
clean: clean_o clean_build clean_libs clean_test

clean_o:
ifdef OBJECTS
	rm *.o
endif

clean_libs:
ifdef LIBS
	rm *.a
endif

clean_build:
	rm -rf $(BUILD_CAT)
	rm -rf $(BUILD_GREP)
	rm -rf $(BUILD_CAT_TEST)
	rm -rf $(BUILD_GREP_TEST)


clean_test:
	@rm -rf report_cat/ report_grep/ gcov_test_* exe *.gcda *.gcno *.info

lint: clean lint_launch clean

lint_launch:
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../materials/linters/cpplint.py --extensions=c grep/*.c cat/*.c grep/*.h cat/*.h
	@rm -rf CPPLINT.cfg

lint_clean:
	@rm CPPLINT.cfg

check: clean
	@cppcheck grep/*.c cat/*.c grep/*.h cat/*.h

leaks_cat: test_cat
	CK_FORK=no leaks --atExit -- ./test_cat
	@make clean

leaks_grep: test_grep
	CK_FORK=no leaks --atExit -- ./test_grep
	@make clean

git: clean
ifdef SOURCES_CAT
	git add ${SOURCES_CAT}
endif
ifdef SOURCES_GREP
	git add ${SOURCES_GREP}
endif
ifdef SOURCES_COMMON
	git add ${SOURCES_COMMON}
endif
ifdef SOURCES_TEST
	git add ${SOURCES_TEST}
endif
ifdef HEADERS_CAT
	git add ${HEADERS_CAT}
endif
ifdef HEADERS_COMMON
	git add ${HEADERS_COMMON}
endif
ifdef HEADERS_GREP
	git add ${HEADERS_GREP}
endif
ifdef HEADERS_TEST
	git add ${HEADERS_TEST}
endif
	git add Makefile
	git add cat/Makefile
	git add grep/Makefile
	git commit -m "${NICKNAME} '${m}' commit at $(DATE_TIME)"
	git push origin develop

merge: git
	git merge origin/develop

valgrind_cat: test_cat
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_cat_test

valgrind_grep: test_grep
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_grep_test
