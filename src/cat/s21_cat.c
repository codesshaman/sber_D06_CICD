#include "s21_cat.h"

int main(int argc, char **argv) {
  Flags flags;
  FILE *file;
  s21_reset(&flags);
  parser(argc, argv, &flags);
  int num_l = 1;
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] != '-') {
      if ((file = fopen(argv[j], "r")) == NULL) {
        perror(argv[j]);
      } else {
        int c;
        int num = 1;
        int count_for_s = 0;
        char prev_c = '\n';
        while ((c = getc(file)) != EOF) {
          if (s21_flag_s(&c, flags, &num, &num_l, &prev_c, &count_for_s) == 1)
            continue;
          count_for_s = 0;
          s21_flag_n(flags, &num, &num_l, &prev_c);
          s21_flag_b(&c, flags, &num, &num_l, &prev_c);
          s21_flag_t(&c, flags, file);
          s21_flag_e(&c, flags);
          s21_flag_v(&c, flags);
          fprintf(stdout, "%c", c);
          prev_c = c;
        }
        fclose(file);
      }
      //            fclose(file);
    }
  }
}

int s21_flag_s(const int *c, Flags flags, int *num, int *num_l, char *prev_c,
               int *count_for_s) {
  int f = 0;
  if (flags.s == 1 && *prev_c == '\n' && *c == '\n') {
    *count_for_s += 1;
    f = 1;
  } else {
    if (*count_for_s > 0 && flags.n == 0 && flags.b == 0 && flags.nl == 0 &&
        flags.bl == 0) {
      if (flags.e) fprintf(stdout, "%s", "$");
      fprintf(stdout, "%c", *prev_c);
    }
    if (*count_for_s > 0 && flags.b == 0 && flags.bl == 0 &&
        (flags.n == 1 || flags.nl == 1)) {
      if (flags.n == 1) {
        fprintf(stdout, "%6d\t", *num);
        *num += 1;
      }
      if (flags.nl == 1) {
        fprintf(stdout, "%6d\t", *num_l);
        *num_l += 1;
      }
      if (flags.e == 1) fprintf(stdout, "%s", "$");
      fprintf(stdout, "%c", *prev_c);
    }
    if (*count_for_s > 0 && (flags.b == 1 || flags.bl == 1) &&
        (flags.n <= 1 || flags.nl <= 1)) {
      if (flags.e == 1) fprintf(stdout, "%s", "$");
      fprintf(stdout, "%c", *prev_c);
    }
  }
  return f;
}

void s21_flag_n(Flags flags, int *num, int *num_l, const char *prev_c) {
  if (flags.n == 1 && flags.b == 0 && (*num == 1 || *prev_c == '\n')) {
    fprintf(stdout, "%6d\t", *num);
    *num += 1;
  }
  if (flags.nl == 1 && flags.bl == 0 && (*num_l == 1 || *prev_c == '\n')) {
    fprintf(stdout, "%6d\t", *num_l);
    *num_l += 1;
  }
}

void s21_flag_b(const int *c, Flags flags, int *num, int *num_l,
                const char *prev_c) {
  if (flags.b == 1 && *prev_c == '\n' && *c != '\n') {
    fprintf(stdout, "%6d\t", *num);
    *num += 1;
  }
  if (flags.bl == 1 && *prev_c == '\n' && *c != '\n') {
    fprintf(stdout, "%6d\t", *num_l);
    *num_l += 1;
  }
}

void s21_flag_t(int *c, Flags flags, FILE *file) {
  if (flags.t == 1) {
    while (*c == '\t') {
      fprintf(stdout, "%s", "^I");
      *c = getc(file);
    }
  }
}

void s21_flag_e(const int *c, Flags flags) {
  if (flags.e == 1 && *c == '\n') fprintf(stdout, "%s", "$");
}

void s21_flag_v(int *c, Flags flags) {
  if (flags.v == 1) {
    if ((*c >= 0 && *c < 9) || (*c > 10 && *c <= 31)) {
      *c += 64;
      printf("^");
    } else if (*c == 127) {
      *c -= 64;
      printf("^");
    } else if (*c >= 128 && *c <= 159) {
      *c -= 64;
      printf("M-^");
    }
  }
}

void s21_reset(Flags *flags) {
  flags->b = 0;
  flags->v = 0;
  flags->s = 0;
  flags->t = 0;
  flags->n = 0;
  flags->e = 0;
  flags->nl = 0;
  flags->bl = 0;
}

void parser(int argc, char **argv, Flags *flags) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0) flags->bl = 1;
      if (strcmp(argv[i], "--number") == 0) flags->nl = 1;
      if (strcmp(argv[i], "--squeeze-blank") == 0) flags->s = 1;
    }
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        switch (argv[i][j]) {
          case 'T':
            flags->t = 1;
            flags->v = 0;
            break;
          case 'E':
            flags->e = 1;
            flags->v = 0;
            break;
          case 'e':
            flags->e = 1;
            flags->v = 1;
            break;
          case 't':
            flags->t = 1;
            flags->v = 1;
            break;
          case 'v':
            flags->v = 1;
            break;
          case 'b':
            flags->b = 1;
            break;
          case 'n':
            flags->n = 1;
            break;
          case 's':
            flags->s = 1;
            break;
          default:
            perror(argv[i]);
            break;
        }
      }
    }
  }
}
