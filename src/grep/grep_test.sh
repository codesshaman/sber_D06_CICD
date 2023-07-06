#!/bin/bash

# one file one flag
echo "TEST -e"
./s21_grep -e GNU -e Front test2.txt > s21_grep.txt
grep -e GNU -e Front test2.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -i"
./s21_grep -i nIcE any_file.txt > s21_grep.txt
grep -i nIcE any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -c"
./s21_grep -c nice any_file.txt > s21_grep.txt
grep -c nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -v"
./s21_grep -v nice any_file.txt > s21_grep.txt
grep -v nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -n"
./s21_grep -n nice any_file.txt > s21_grep.txt
grep -n nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -h"
./s21_grep -h nice any_file.txt > s21_grep.txt
grep -h nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -e fail file"
./s21_grep -e nice any_file.tt > s21_grep.txt
grep -e nice any_file.tt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -s"
./s21_grep -s nice any_file.txt > s21_grep.txt
grep -s nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -o"
./s21_grep -o nice any_file.txt > s21_grep.txt
grep -o nice any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt
#
echo "TEST -f"
./s21_grep -f pattern.txt any_file.txt > s21_grep.txt
grep -f pattern.txt any_file.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt


#two file one flag
echo "TEST -e two files"
./s21_grep -e nice any_file.txt test.txt > s21_grep.txt
grep -e nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -i two files"
./s21_grep -i nIcE any_file.txt test.txt > s21_grep.txt
grep -i nIcE any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -c two files"
./s21_grep -c nice any_file.txt test.txt > s21_grep.txt
grep -c nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -v two files"
./s21_grep -v nice any_file.txt test.txt > s21_grep.txt
grep -v nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -n two files"
./s21_grep -n nice any_file.txt test.txt > s21_grep.txt
grep -n nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -h"
./s21_grep -h nice any_file.txt test.txt > s21_grep.txt
grep -h nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -e two file (fail file)"
./s21_grep -e nice any_file.tt test.txt > s21_grep.txt
grep -e nice any_file.tt test.txt> grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -s"
./s21_grep -s nice any_file.tt test.txt > s21_grep.txt
grep -s nice any_file.tt test.txt> grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -o"
./s21_grep -o nice any_file.txt test.txt > s21_grep.txt
grep -o nice any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt

echo "TEST -f"
./s21_grep -f pattern.txt any_file.txt test.txt > s21_grep.txt
grep -f pattern.txt any_file.txt test.txt > grep.txt
diff -s s21_grep.txt grep.txt
rm s21_grep.txt grep.txt
