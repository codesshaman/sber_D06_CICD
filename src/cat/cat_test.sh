#!/bin/bash

echo "TEST1"
./s21_cat -n 1.txt spec.txt > s21_cat.txt
cat -n 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST2"
./s21_cat -e 1.txt spec.txt > s21_cat.txt
cat -e 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST3"
./s21_cat -n 1.txt spec.txt > s21_cat.txt
cat -n 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST4"
./s21_cat -s 1.txt spec.txt > s21_cat.txt
cat -s 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST5"
./s21_cat -t 1.txt spec.txt > s21_cat.txt
cat -t 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST6"
./s21_cat -b -n 1.txt spec.txt > s21_cat.txt
cat -b -n 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST7"
./s21_cat -sn spec.txt > s21_cat.txt
cat -sn spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#
echo "TEST8"
./s21_cat -et 1.txt spec.txt > s21_cat.txt
cat -et 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST9"
./s21_cat -en 1.txt spec.txt > s21_cat.txt
cat -en 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST10"
./s21_cat -tn 1.txt spec.txt > s21_cat.txt
cat -tn 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST11"
./s21_cat -tb 1.txt spec.txt > s21_cat.txt
cat -tb 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST12"
./s21_cat -ts 1.txt spec.txt > s21_cat.txt
cat -ts 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST13"
./s21_cat -bnste 1.txt spec.txt > s21_cat.txt
cat -bnste 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo "TEST14"
./s21_cat -b -n -s -t -e 1.txt spec.txt > s21_cat.txt
cat -b -n -s -t -e 1.txt spec.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
