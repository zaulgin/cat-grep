#include "cat_functions.h"

void print_files(char *files[], Cat_flags *flags, int file_count) {
  int row_count = 1;

  for (int i = 0; i < file_count; i++) {
    FILE *f = fopen(files[i], "r");
    if (f == NULL) {
      printf("%s: Нет такого файла или каталога\n", files[i]);
      continue;
    }

    int res;
    char ch;
    char tmp_ch;

    int empty_line_count = 0;

    while ((res = fgetc(f)) != EOF) {
      ch = res;
      bool tabs = false;
      if (flags->is_delete_empty_line) {
        if (tmp_ch == '\n') {
          empty_line_count++;
        } else {
          empty_line_count = 0;
        }
        if (ch == '\n' && empty_line_count > 1) {
          tmp_ch = ch;
          continue;
        }
      }

      if (flags->is_all_line_numbers) {
        if (tmp_ch == '\n' || row_count == 1) {
          print_line_number(&row_count);
        }
      }

      if (flags->is_non_empty_line_numbers) {
        if ((tmp_ch == '\n' && ch != '\n') || row_count == 1) {
          print_line_number(&row_count);
        }
      }

      if (flags->is_end_of_string) {
        if (ch == '\n') {
          fputc('$', stdout);
        }
      }

      if (flags->is_tabs) {
        if (ch == '\t') {
          fputs("^I", stdout);
          tabs = true;
        }
      }

      if (flags->is_nonprinting_chars) {
        if ((unsigned char)ch > 127) {
          char buf[] = {ch, 0};
          for (int i = 0; i < (int)strlen(buf); i++) {
            char uc = (unsigned char)buf[i] & 127;
            if (uc < 32) {
              printf("M-^%c", uc + 64);
            } else if (uc == 127) {
              printf("M-^?");
            } else {
              printf("M-%c", uc);
            }
          }
          tmp_ch = ch;
          continue;
        } else if ((unsigned char)ch < 32 && ch != 9 && ch != 10 && ch != 12) {
          printf("^%c", ch + 64);
          tmp_ch = ch;
          continue;
        } else if (ch == 127) {
          printf("^?");
          tmp_ch = ch;
          continue;
        } else if (ch == 12) {
          printf("^L");
          tmp_ch = ch;
          continue;
        }
      }

      if (!tabs) {
        fputc(ch, stdout);
      }
      tmp_ch = ch;
      tabs = false;
    }
    fclose(f);
  }
}

void print_line_number(int *row_count) {
  printf("%*d\t", 6, *row_count);
  (*row_count)++;
}