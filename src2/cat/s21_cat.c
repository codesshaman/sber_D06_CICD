#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    opt flag;
    s21_init(&flag);
    if (s21_parse_opt(argc, argv, &flag) == 0) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') s21_output_result(argv[i], flag);
      }
    }
  }
  return 0;
}

void s21_init(opt *flag) {
  flag->b = 0;
  flag->e = 0;
  flag->n = 0;
  flag->s = 0;
  flag->t = 0;
  flag->v = 0;
}

int s21_parse_opt(int argc, char **argv, opt *flag) {
  int error = 0;
  for (int i = 1; i < argc; i++) {
    int j = 1;
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      while (argv[i][j] != '\0') {  // пока не конец строки
        if (argv[i][j] == 'b') {
          flag->b = 1;
        } else if (argv[i][j] == 'e') {
          flag->e = 1;
          flag->v = 1;
        } else if (argv[i][j] == 'n') {
          flag->n = 1;
        } else if (argv[i][j] == 's') {
          flag->s = 1;
        } else if (argv[i][j] == 't') {
          flag->t = 1;
          flag->v = 1;
        } else if (argv[i][j] == 'v') {
          flag->v = 1;
        } else if (argv[i][j] == 'E') {
          flag->e = 1;
        } else if (argv[i][j] == 'T') {
          flag->t = 1;
        } else {
          printf("cat: illegal option -- %c\n", argv[1][i]);
          printf("usage: cat [-benstuv] [file ...]\n");
          error = 1;
          break;
        }
        j++;
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-' &&
               argv[i][2] != '-') {  // др флаги если (--)
      if (strcmp(argv[i], "--number-nonblank") ==
          0) {  //  если арг равен этому слову - это флаг
        flag->b = 1;
      } else if (strcmp(argv[i], "--number") == 0) {
        flag->n = 1;
      } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        flag->s = 1;
      } else {
        printf("cat: illegal option -- %c\n", argv[1][i]);
        printf("usage: cat [-benstuv] [file ...]\n");
        error = 1;
      }
      j++;
    } else if (argv[i][0] == '-' && argv[i][1] == '-' &&
               argv[i][2] == '-') {  // если (---)
      printf("cat: illegal option -- -\n");
      printf("usage: cat [-benstuv] [file ...]\n");
      error = 1;
    }
  }
  return error;
}

void s21_output_result(char *argv, opt flag) {
  FILE *file;
  int c;
  if ((file = fopen(argv, "r")) == NULL) {
    printf("s21_cat: %s: No such file or directory\n", argv);
  } else {
    int before_char = '\n';
    int count = 0;
    int i = 1;
    while ((c = fgetc(file)) != EOF) {
      if (flag.s && c == '\n' && (before_char == '\n' || before_char == '\0')) {
        count++;  // amount symbols in str
      } else {
        count = 0;
      }
      if (count <= 1) {
        if (((flag.n && before_char == '\n') && !flag.b) ||
            (flag.b && before_char == '\n' && c != '\n')) {
          printf("%6d\t", i++);
        }
        if ((!flag.t && !flag.e) && flag.v) {
          s21_flag_v(&c);
        }
        s21_flag_e(flag, &c);  //?
        s21_flag_t(flag, &c);
        putchar(c);
        before_char = c;
      }
    }
    fclose(file);
  }
}

void s21_flag_e(opt flag, int *c) {
  if (flag.e) {
    if (*c == '\n') {
      printf("$");  // read
    }
    if (flag.v) {
      s21_flag_v(c);
    }
  }
}

void s21_flag_t(opt flag, int *c) {
  if (*c == '\t' && flag.t) {
    *c = '^';
    putchar(*c);
    *c = 'I';
  }
  if (flag.v) {
    s21_flag_v(c);
  }
}

void s21_flag_v(int *c) {
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
