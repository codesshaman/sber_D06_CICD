#!/bin/bash

scp /home/gitlab-runner/builds/BeuVcSKy/0/students/DO6_CICD.ID_356283/milagros_student.21_school.ru/DO6_CICD-1/src/cat/s21_cat milagros@10.10.0.2:/usr/local/bin
scp /home/gitlab-runner/builds/BeuVcSKy/0/students/DO6_CICD.ID_356283/milagros_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep milagros@10.10.0.2:/usr/local/bin
ssh milagros@10.10.0.2 ls -lah /usr/local/bin
