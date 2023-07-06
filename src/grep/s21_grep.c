#include "s21_grep.h"

int main(int argc, char *argv[]) {
  parse_input_string(argc, argv);
  return 0;
}

void parse_input_string(int argc, char *argv[]) {
  unsigned int flag = 0;
  FORMAT FFormat = {0};
  int i = 1;
  while (i < argc && FFormat.flag_error == 0) {
    if (argv[i][0] == '-') {
      parse_grep_flags(argv[i], &FFormat, &i, argv);
    } else {
      FFormat.file_cnt++;
    }
    i++;
  }
  if (FFormat.flag_e == 0 && FFormat.flag_f == 0) FFormat.file_cnt--;

  i = 1;
  while (i < argc && FFormat.flag_error == 0) {
    if (argv[i][0] == '-') {
      if (strstr(argv[i], "e") || strstr(argv[i], "f")) {
        i++;
      }
    } else if (FFormat.flag_e == 0 && FFormat.flag_f == 0 && flag == 0) {
      e_to_pattern_str(argv[i], &FFormat);
      flag = 1;
    } else {
      formated_file_print(argv[i], &FFormat);
    }
    if (FFormat.flag_error == 0) {
      i++;
    }
  }

  if (FFormat.template) free(FFormat.template);

  if (FFormat.flag_error > 0) {
    if (FFormat.flag_error == 1 && argv[i][0] == '-') {
      fprintf(stderr, "grep: illegal option -%c\n", FFormat.str_err);
      fprintf(stderr, "usage: grep [-eivclnhsfo] [pattern] [file ...]\n");
    } else {
      fprintf(stderr, "usage: grep [-eivclnhsfo] [pattern] [file ...]\n");
    }
  }
}

void e_to_pattern_str(char *pattern, FORMAT *FFormat) {
  char *p = NULL;
  unsigned int str_len_template = 0;

  regex_t reg;
  int cflags = REG_EXTENDED | REG_NEWLINE;
  if (regcomp(&reg, pattern, cflags)) {
    pattern = NULL;
  } else {
    regfree(&reg);
  }

  if (FFormat->template) {
    str_len_template = strlen(FFormat->template);
  }
  if (pattern != NULL) {
    p = calloc((strlen(pattern) + str_len_template + 50), sizeof(char));
  }

  if (p) {
    if (FFormat->template) {
      sprintf(p, "%s|%s", FFormat->template, pattern);
      free(FFormat->template);
    } else {
      sprintf(p, "%s", pattern);
    }
    FFormat->template = p;
  }
}

void f_to_pattern_str(char *file_name, FORMAT *FFormat) {
  FILE *fp = NULL;
  char line_buff[1024] = "";
  int ch;
  fp = fopen(file_name, "r");

  if (fp == NULL) {
    if (FFormat->flag_s != 1) {
      fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
    }
  } else {
    ch = fgetc(fp);
    int cnt = 0;
    while (1) {
      if ((cnt == sizeof(line_buff) - 1) || ch == '\n' || ch == EOF) {
        line_buff[cnt] = '\0';
        if (strlen(line_buff)) {
          e_to_pattern_str(line_buff, FFormat);
        }
        cnt = 0;
        if (ch == EOF) break;
      } else {
        line_buff[cnt] = (char)ch;
        cnt++;
      }
      ch = fgetc(fp);
    }
    fclose(fp);
  }
}

void parse_grep_flags(char *str, FORMAT *FFormat, int *n, char *argv[]) {
  while (*(++str) != '\0') {
    switch (*str) {
      case 'e':
        e_to_pattern_str(argv[*n + 1], FFormat);
        *n += 1;
        FFormat->flag_e = 1;
        break;
      case 'i':
        FFormat->flag_i = 1;
        break;
      case 'v':
        FFormat->flag_v = 1;
        break;
      case 'c':
        FFormat->flag_c = 1;
        break;
      case 'l':
        FFormat->flag_l = 1;
        break;
      case 'n':
        FFormat->flag_n = 1;
        break;
      case 'h':
        FFormat->flag_h = 1;
        break;
      case 's':
        FFormat->flag_s = 1;
        break;
      case 'f':
        f_to_pattern_str(argv[*n + 1], FFormat);
        *n += 1;
        FFormat->flag_f = 1;
        break;
      case 'o':
        FFormat->flag_o = 1;
        break;
      default:
        FFormat->flag_error = 1;
        FFormat->str_err = *str;
    }
  }
}

void formated_file_print(char *str, FORMAT *FFormat) {
  FILE *fp = NULL;
  fp = fopen(str, "r");

  if (fp == NULL) {
    if (FFormat->flag_s != 1) {
      fprintf(stderr, "grep: %s: No such file or directory\n", str);
    }
  } else {
    int cflags = REG_EXTENDED | REG_NEWLINE;

    if (FFormat->flag_i == 1) {
      cflags |= REG_ICASE;
    }

    regex_t reg;

    if (FFormat->template) {
      regcomp(&reg, FFormat->template, cflags);

      int line_cnt = 0;
      file_processing(str, fp, &reg, &line_cnt, FFormat);

      flag_lc_print(str, line_cnt, FFormat);
      regfree(&reg);
    }
    fclose(fp);
  }
}

void file_processing(char const *str, FILE *fp, regex_t *reg, int *line_cnt,
                     FORMAT *FFormat) {
  char line_buff[1024] = "";
  char line_buff2[1024] = "";
  int ch;
  int cnt = 0;
  int file_line_cnt = 0;
  regmatch_t regmatch[1];
  ch = fgetc(fp);
  while (1) {
    if ((cnt == sizeof(line_buff) - 1) || ch == '\n' || ch == EOF) {
      if (ch == '\n') {
        line_buff[cnt++] = '\n';
        file_line_cnt++;
      }
      line_buff[cnt] = '\0';
      size_t len_buff = strlen(line_buff);
      size_t offset = 0;
      if (len_buff) {
        int match_res = regexec(reg, line_buff, 1, regmatch, 0);
        if (ch == EOF) {
          line_buff[cnt++] = '\n';
          line_buff[cnt] = '\0';
        }

        if (match_res == 0 && FFormat->flag_v == 0) {
          if (FFormat->flag_o == 1) {
            unsigned int exit_fl = 0;
            do {
              size_t buff_len = regmatch->rm_eo - regmatch->rm_so;
              strncat(line_buff2, line_buff + offset + regmatch->rm_so,
                      buff_len);
              strcat(line_buff2, "\n");

              offset += regmatch->rm_eo;

              if (regmatch->rm_so == regmatch->rm_eo) {
                offset += 1;
              }

              if (offset > len_buff) {
                exit_fl = 1;
              }
            } while (regexec(reg, line_buff + offset, 1, regmatch, 0) !=
                         REG_NOMATCH ||
                     exit_fl == 1);

            strcpy(line_buff, line_buff2);
            strcpy(line_buff2, "");
          }

          if (FFormat->flag_l == 1 && *line_cnt == 0)
            *line_cnt = 1;
          else if (FFormat->flag_l == 0)
            *line_cnt += 1;

          finded_line_print(str, line_buff, file_line_cnt, FFormat);

        } else if (match_res == REG_NOMATCH && FFormat->flag_v == 1) {
          if (FFormat->flag_l == 1 && *line_cnt == 0)
            *line_cnt = 1;
          else if (FFormat->flag_l == 0)
            *line_cnt += 1;

          finded_line_print(str, line_buff, file_line_cnt, FFormat);
        }
      }
      cnt = 0;
      if (ch == EOF) break;
    } else {
      line_buff[cnt] = (char)ch;
      cnt++;
    }
    ch = fgetc(fp);
  }
}

void flag_lc_print(char *str, int line_cnt, FORMAT *FFormat) {
#if defined(__APPLE__) || (__MACH__)
  if (FFormat->flag_c == 1) {
#else
  if (FFormat->flag_c == 1 && FFormat->flag_l == 0) {
#endif
    if (FFormat->file_cnt == 1) {
      printf("%d\n", line_cnt);
    } else {
      if (FFormat->flag_h == 0) {
        printf("%s:%d\n", str, line_cnt);
      } else {
        printf("%d\n", line_cnt);
      }
    }
  }
  if (FFormat->flag_l == 1 && line_cnt > 0) {
    printf("%s\n", str);
  }
}

void finded_line_print(char const *file_name, char *str, int cnt,
                       FORMAT *FFormat) {
  if (FFormat->flag_c == 0 && FFormat->flag_l == 0) {
    if (FFormat->file_cnt > 1 && FFormat->flag_n == 1) {
      if (FFormat->flag_h == 0)
        printf("%s:%d:%s", file_name, cnt, str);
      else
        printf("%d:%s", cnt, str);
    } else if (FFormat->file_cnt > 1 && FFormat->flag_n == 0) {
      if (FFormat->flag_h == 0)
        printf("%s:%s", file_name, str);
      else
        printf("%s", str);
    } else if (FFormat->file_cnt == 1 && FFormat->flag_n == 1) {
      printf("%d:%s", cnt, str);
    } else if (FFormat->file_cnt == 1 && FFormat->flag_n == 0) {
      printf("%s", str);
    }
  }
}
