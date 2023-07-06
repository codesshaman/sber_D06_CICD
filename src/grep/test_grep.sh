#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="test1.txt"
TEST_FILE2="test2.txt"
TEST_FILE3="test3.txt"
TEST_FILE4="test4.txt"

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in a i o f.txt qwerty a.g a\ opt 1-5 1 1+5 Ar
  do
          TEST1="$var1 $var2 $TEST_FILE1"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
  done
done

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in a i o f.txt qwerty a.g a\ opt 1-5 1 1+5 Ar
  do
          TEST1="$var1 $var2 $TEST_FILE2"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
  done
done

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in a i o f.txt qwerty a.g a\ opt 1-5 1 1+5 Ar
  do
          TEST1="$var1 $var2 $TEST_FILE3"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
  done
done

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in a i o f.txt qwerty a.g a\ opt 1-5 1 1+5 Ar
  do
          TEST1="$var1 $var2 $TEST_FILE4"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
  done
done

###################################################################################################

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in e i v c l n h s f o
  do
    for var3 in a i o f.txt qwerty a.g  opt 1-5 1 1+5 Ar
    do
          TEST1="$var1$var2 $var3 $TEST_FILE2"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
    done
  done
done

for var1 in -e -i -v -c -l -n -h -s -f -o
do
  for var2 in e i v c l n h s f o
  do
    for var3 in a i o f.txt qwerty a.g  opt 1-5 1 1+5 Ar
    do
          TEST1="$var1$var2 $var3 $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

