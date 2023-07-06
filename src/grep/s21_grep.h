#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

typedef struct format {
    unsigned int flag_e;
    unsigned int flag_i;
    unsigned int flag_v;
    unsigned int flag_c;
    unsigned int flag_l;
    unsigned int flag_n;
    unsigned int flag_h;
    unsigned int flag_s;
    unsigned int flag_f;
    unsigned int flag_o;
    unsigned int flag_error;
    unsigned int file_cnt;
    char *template;
    char str_err;
} FORMAT;

void e_to_pattern_str(char *pattern, FORMAT *FFormat);
void f_to_pattern_str(char *file_name, FORMAT *FFormat);

void formated_file_print(char *str, FORMAT *FFormat);
void parse_input_string(int argc, char *argv[]);

void check_long_parameter(char *str, FORMAT *FFormat);
void parse_grep_flags(char *str, FORMAT *FFormat, int *n, char *argv[]);
void finded_line_print(char const *file_name, char *str, int cnt, FORMAT *FFormat);
void flag_lc_print(char *str, int line_cnt, FORMAT *FFormat);
void file_processing(char const *str, FILE *fp, regex_t *reg, int *line_cnt, FORMAT *FFormat);

#endif  //  SRC_GREP_S21_GREP_H_
