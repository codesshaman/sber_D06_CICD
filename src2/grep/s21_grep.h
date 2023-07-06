#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <pcre.h>
#include <stdio.h>
#include <string.h>

#define OVECCOUNT 30

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int count_files;
  int presence_flag;
  int count_flags;
  int count_e;
  int count_f;
} opt;

void s21_init(opt *flags);
int s21_parse_flags(int argc, char **argv, opt *flags);
char **check_regex_and_files(int argc, char **argv, opt *flags,
                             char **mas_with_reg_exp, char **mas_with_files);
void s21_running(opt flags, char *mas_with_reg_exp, char **mas_with_files);
void s21_output_result(opt flags, char *name_file, char *reg_exp);
void check_e_flags(char **argv, char **mas_with_reg_exp, int *i, int *j);
void check_f_flag(char **argv, char **mas_with_reg_exp, int *i, opt flags);

#endif  //  SRC_GREP_S21_GREP_H_
