#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
} opt;

void s21_init(opt *flag);
int s21_parse_opt(int argc , char **argv, opt *flag);
void s21_output_result(char *argv, opt flag);
void s21_flag_e(opt flag, int *c);
void s21_flag_t(opt flag, int *c);
void s21_flag_v(int *c);

#endif  // SRC_CAT_S21_CAT_H_
