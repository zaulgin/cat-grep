#include "grep_functions.h"

void output(char *files[], Grep_flags flags, Grep_behavior behavior,
            int file_count, char *pattern) {
  bool output_var;  // переменная для флага -v
  char buf[1000];
  char buf_output[1000];
  int count_rows, row_num;
  char prefix[100] = "";

  // Преобразование шаблона в нижний регистр, если установлен флаг -i
  if (flags.is_register_ignore) {
    str_lower(pattern);
  }

  for (int i = 0; i < file_count; i++) {
    FILE *f = fopen(files[i], "r");
    if (f == NULL) {
      if (!flags.is_file_error_ignore) {  // флаг -s - не выводит сообщение об
                                          // ошибке если true
        printf("%s: Нет такого файла или каталога\n", files[i]);
      }
      continue;
    }

    count_rows = 0;
    row_num = 0;
    bool file_printed =
        false;  // флаг, чтобы избежать повторного вывода имени файла

    while (fgets(buf, 1000, f)) {
      strcpy(buf_output, buf);
      row_num++;

      if (behavior.many_files) {
        strcat(prefix, files[i]);
        strcat(prefix, ":");
      }

      if (flags.is_register_ignore) {  // Преобразование строки в нижний
                                       // регистр, если установлен флаг -i
        str_lower(buf);
      }

      output_var = strstr(buf, pattern);

      if (flags.is_invert_results) {  // флаг -v - инвертирует результаты
        output_var = !output_var;
      }

      if (output_var) {
        if (flags.is_only_filename) {  // флаг -l выводит имя файла
          printf("%s\n", files[i]);
          file_printed = true;
          break;
        }
        if (flags.is_count_rows) {  // флаг -c выводит кол-во строк
          count_rows++;
        } else {
          if (flags.is_num_row) {
            char temp[11];
            sprintf(temp, "%d", row_num);
            strcat(prefix, temp);
            strcat(prefix, ":");
          }
          printf("%s%s", prefix, buf_output);
        }
      }
      strcpy(prefix, "");
    }

    if (file_printed) {
      fclose(f);
      continue;
    }

    if (flags.is_count_rows) {
      strcat(prefix, files[i]);
      strcat(prefix, ":");
      printf("%s%d\n", prefix, count_rows);
    }

    fclose(f);
  }
}

char *str_lower(char *string) {
  unsigned char *p = (unsigned char *)string;
  while (*p) {
    *p = tolower(*p);
    p++;
  }
  return string;
}