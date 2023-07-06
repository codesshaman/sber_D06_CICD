#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    char *mas_with_reg_exp = NULL;
    char **mas_with_files = NULL;
    opt flags;
    s21_init(&flags);
    if (s21_parse_flags(argc, argv, &flags) == 0) {
      mas_with_files = check_regex_and_files(argc, argv, &flags,
                                             &mas_with_reg_exp, mas_with_files);
      s21_running(flags, mas_with_reg_exp, mas_with_files);
    }
    free(mas_with_reg_exp);
    for (int i = 0; i <= flags.count_files; i++) {
      free(mas_with_files[i]);
    }
    free(mas_with_files);
  }
  return 0;
}

void s21_init(opt *flags) {
  flags->e = 0;
  flags->i = 0;
  flags->v = 0;
  flags->c = 0;
  flags->l = 0;
  flags->n = 0;
  flags->h = 0;
  flags->s = 0;
  flags->f = 0;
  flags->o = 0;
  flags->count_files = 0;
  flags->presence_flag = 0;
  flags->count_flags = 0;
  flags->count_e = 0;
  flags->count_f = 0;
}

int s21_parse_flags(int argc, char **argv, opt *flags) {
  int fail = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      int j = 1;
      while (argv[i][j] != '\0') {
        if (argv[i][j] == 'e') {
          flags->e = 1;
          flags->count_e++;
          break;
        } else if (argv[i][j] == 'i') {
          flags->i = 1;
        } else if (argv[i][j] == 'v') {
          flags->v = 1;
        } else if (argv[i][j] == 'c') {
          flags->c = 1;
        } else if (argv[i][j] == 'l') {
          flags->l = 1;
        } else if (argv[i][j] == 'n') {
          flags->n = 1;
        } else if (argv[i][j] == 'h') {
          flags->h = 1;
        } else if (argv[i][j] == 's') {
          flags->s = 1;
        } else if (argv[i][j] == 'f') {
          flags->f = 1;
          flags->count_f++;
          break;
        } else if (argv[i][j] == 'o') {
          flags->o = 1;
        } else {
          printf("error");
          fail = 1;
          break;
        }
        j++;
        flags->presence_flag = 1;
      }
    }
  }
  return fail;
}

char **check_regex_and_files(int argc, char **argv, opt *flags,
                             char **mas_with_reg_exp, char **mas_with_files) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      int j = 1;
      while (argv[i][j] != '\0') {
        if (argv[i][j] == 'e') {
          check_e_flags(argv, mas_with_reg_exp, &i, &j);
          break;
        } else if (argv[i][j] == 'f') {
          check_f_flag(argv, mas_with_reg_exp, &i, *flags);
          break;
        }
        j++;
      }
    } else {
      if (!flags->e && !flags->f && *mas_with_reg_exp == NULL) {
        *mas_with_reg_exp =
            realloc(*mas_with_reg_exp, (strlen(argv[i]) + 1) * sizeof(char));
        strcpy(*mas_with_reg_exp, argv[i]);
      } else {
        flags->count_files++;
        mas_with_files = realloc((char **)mas_with_files,
                                 (flags->count_files + 1) * sizeof(char *));
        mas_with_files[flags->count_files] = NULL;
        mas_with_files[flags->count_files - 1] = NULL;
        mas_with_files[flags->count_files - 1] =
            realloc(mas_with_files[flags->count_files - 1],
                    (strlen(argv[i]) + 1) * sizeof(char));
        strcpy(mas_with_files[flags->count_files - 1], argv[i]);
      }
    }
  }
  return mas_with_files;
}

void s21_running(opt flags, char *mas_with_reg_exp, char **mas_with_files) {
  for (int i = 0; i < flags.count_files; i++) {
    s21_output_result(flags, mas_with_files[i], mas_with_reg_exp);
  }
}

void s21_output_result(opt flags, char *name_file, char *reg_exp) {
  FILE *file;
  pcre *pcre;
  if ((file = fopen(name_file, "r")) == NULL) {
    if (!flags.s) {
      printf("s21_grep: %s: No such file or directory\n", name_file);
    }
  } else {
    char *str = NULL;
    const char *error;
    int erroffset;
    size_t len = 0;
    int flag_i = 0;
    int flag_v = 1;
    int rc;
    int ovector[OVECCOUNT];
    int count_success_srting = 0;
    int number_string = 0;
    if (flags.i) {
      flag_i = PCRE_CASELESS;
    }
    if (flags.v) {
      flag_v = -1;
    }
    int write_count_files = 0;
    int my_free = 0;
    while (getline(&str, &len, file) != -1) {
      number_string++;
      if (reg_exp == NULL) {
        my_free = 1;
        break;
      }
      pcre = pcre_compile(reg_exp, flag_i, &error, &erroffset, NULL);
      if (pcre == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
      } else {
        rc = pcre_exec(pcre, NULL, str, strlen(str), 0, 0, ovector, OVECCOUNT);
      }
      if (rc == flag_v) {
        count_success_srting++;
        if ((flags.l || flags.count_files > 1) && !flags.h &&
            !write_count_files) {
          if (flags.c && flags.count_files != 1 && !flags.n && !flags.o) {
            printf("%s:", name_file);
            write_count_files = 1;
            pcre_free((void *)pcre);
            my_free = 1;
            if (!flags.l) {
              continue;
            } else {
              break;
            }
          } else if (flags.c && (flags.n || flags.o) && !write_count_files &&
                     flags.count_files > 1) {
            printf("%s:", name_file);
            write_count_files = 1;
          } else if (!flags.h && flags.count_files > 1 && !flags.l) {
            printf("%s:", name_file);
          }
        }
        if (flags.n && !flags.c && !flags.l) {
          printf("%d:", number_string);
        }
        if ((flags.o || flags.n || flags.h || flags.s) && !flags.c &&
            !flags.l) {
          if (flags.v) {
            printf("%s", str);
            if (str[strlen(str) - 1] != '\n') {
              printf("\n");
            }
          } else if ((flags.n && !flags.c && !flags.l && !flags.h &&
                      !flags.o) ||
                     (flags.h && !flags.c && !flags.l && !flags.n &&
                      !flags.o) ||
                     (flags.s && !flags.c && !flags.l && !flags.n &&
                      !flags.o) ||
                     (flags.n && flags.h && !flags.o) ||
                     (flags.f && !flags.i && !flags.e) ||
                     (flags.o && flags.f && !flags.e && !flags.i) ||
                     (flags.o && flags.f && flags.e &&
                      (flags.count_e > 1 || flags.count_f > 1))) {
            printf("%s", str);
            if (str[strlen(str) - 1] != '\n') {
              printf("\n");
            }
          } else {
            pcre_extra *f_ext;
            const char *errstr = NULL;
            const char *buf = NULL;
            f_ext = pcre_study(pcre, 0, &errstr);
            int pairs = 0;
            int j = 0;
            while ((pairs = pcre_exec(pcre, f_ext, str, strlen(str), j, 0,
                                      ovector, OVECCOUNT)) > 0) {
              pcre_get_substring(str, ovector, pairs, 0, &buf);
              printf("%s\n", buf);
              pcre_free_substring(buf);
              j = ovector[1] + 1;
            }
            free(f_ext);
          }
        } else if ((flags.e || flags.i || flags.v || !flags.presence_flag) &&
                   !flags.c && !flags.l) {
          printf("%s", str);
          if (str[strlen(str) - 1] != '\n') {
            printf("\n");
          }
        }
        if (flags.l) {
          if (flags.count_files > 1 && !flags.c) printf("%s\n", name_file);
          pcre_free((void *)pcre);
          my_free = 1;
          break;
        }
      }
      pcre_free((void *)pcre);
      my_free = 1;
    }
    if (!my_free) {
      pcre_free(pcre);
    }
    if (write_count_files && (flags.l || flags.c)) {
      if (flags.c) {
        printf("%d\n", count_success_srting);
      }
      if (flags.l) {
        printf("%s\n", name_file);
      }
    } else if (!write_count_files && flags.count_files == 1) {
      if (flags.c) {
        printf("%d\n", count_success_srting);
      }
      if (flags.l) {
        printf("%s\n", name_file);
      }
    } else if (flags.c &&
               (flags.h || flags.n || flags.o || !write_count_files)) {
      if (flags.l && !flags.h) {
        printf("%s:", name_file);
      }
      if (!count_success_srting && !flags.l && flags.count_files > 1 &&
          !flags.h) {
        printf("%s:", name_file);
      }
      printf("%d\n", count_success_srting);
      if (flags.l && count_success_srting >= 1) {
        printf("%s\n", name_file);
      }
    }
    free(str);
  }
  if (file != NULL) {
    fclose(file);
  }
}

void check_e_flags(char **argv, char **mas_with_reg_exp, int *i, int *j) {
  int count = 0;
  if (*mas_with_reg_exp == NULL) {
    count = 1;
  } else {
    count = strlen(*mas_with_reg_exp) + 1;
    *mas_with_reg_exp = realloc(*mas_with_reg_exp, count * sizeof(char));
    (*mas_with_reg_exp)[count - 1] = '|';
    count++;
  }
  if (argv[*i][*j + 1] != '\0' && argv[*i][*j + 1] != '\n') {
    (*j)++;
  } else {
    (*i)++;
    *j = 0;
  }
  for (; argv[*i][*j] != '\0'; (*j)++, count++) {
    *mas_with_reg_exp = realloc(*mas_with_reg_exp, (count + 1) * sizeof(char));
    (*mas_with_reg_exp)[count] = '\0';
    (*mas_with_reg_exp)[count - 1] = argv[*i][*j];
  }
  // memset(argv[*i], 0, strlen(argv[*i]));
}

void check_f_flag(char **argv, char **mas_with_reg_exp, int *i, opt flags) {
  int count = 0;
  (*i)++;
  FILE *file;
  char str[300];
  if ((file = fopen(argv[*i], "r")) == NULL) {
    if (!flags.s) {
      printf("s21_grep: %s: No such file or directory\n", argv[*i]);
    }
  } else {
    while (fgets(str, sizeof(str), file)) {
      if (strlen(str) > 1 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
      }
      if (*mas_with_reg_exp == NULL) {
        count = 1;
        *mas_with_reg_exp =
            realloc(*mas_with_reg_exp, (count + strlen(str)) * sizeof(char));
        strcat(*mas_with_reg_exp, str);
      } else {
        count = strlen(*mas_with_reg_exp) + 2;
        *mas_with_reg_exp =
            realloc(*mas_with_reg_exp, (count + strlen(str)) * sizeof(char));
        strcat(*mas_with_reg_exp, "|");
        strcat(*mas_with_reg_exp, str);
      }
    }
  }
  if (file != NULL) {
    fclose(file);
  }
}
