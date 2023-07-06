#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int b;
    int e;
    int v;
    int s;
    int t;
    int n;
    int sl;
    int nl;
    int bl;
} Flags;

void s21_reset(Flags *flags);
void parser(int argc, char** argv, Flags *flags);
int s21_flag_s(const int *c, Flags flags, int *num, int *num_l, char *prev_c, int *count_for_s);
void s21_flag_n(Flags flags, int *num, int *num_l, const char *prev_c);
void s21_flag_b(const int *c, Flags flags, int *num, int *num_l, const char *prev_c);
void s21_flag_t(int *c, Flags flags, FILE *file);
void s21_flag_e(const int *c, Flags flags);
void s21_flag_v(int *c, Flags flags);
#endif  // SRC_CAT_S21_CAT_H_
