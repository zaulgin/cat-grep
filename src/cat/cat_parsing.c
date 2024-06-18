#include "cat_parsing.h"

// TODO с учетом массива флагов, переделать функцию парсинга: возможно вывести
// инициализацию флагов в отдельную функцию
char *parse_args(int argc, char *argv[], Cat_flags *flags, char *files[],
                 int *file_count) {
  for (int i = 1; i < argc; i++) {
    // обычные флаги
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (int j = 1; j < (int)strlen(argv[i]); j++) {
        switch (argv[i][j]) {
          case 'A':
            flags->is_nonprinting_chars = true;
            flags->is_tabs = true;
            flags->is_end_of_string = true;
            break;
          case 't':
            flags->is_nonprinting_chars = true;
            flags->is_tabs = true;
            break;
          case 'T':
            flags->is_tabs = true;
            break;
          case 'e':
            flags->is_nonprinting_chars = true;
            flags->is_end_of_string = true;
            break;
          case 'E':
            flags->is_end_of_string = true;
            break;
          case 's':
            flags->is_delete_empty_line = true;
            break;
          case 'n':
            if (flags->is_non_empty_line_numbers) {
              break;
            }
            flags->is_all_line_numbers = true;
            break;
          case 'b':
            flags->is_non_empty_line_numbers = true;
            flags->is_all_line_numbers = false;
            break;
          case 'v':
            flags->is_nonprinting_chars = true;
            break;
          default:
            return argv[i];
        }
      }
      // GNU флаги
    } else if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (!strcmp(argv[i], GNU_all_line_numbers)) {
        if (flags->is_non_empty_line_numbers) {
          continue;
        }
        flags->is_all_line_numbers = true;
      } else if (!strcmp(argv[i], GNU_non_empty_line_numbers)) {
        flags->is_non_empty_line_numbers = true;
        flags->is_all_line_numbers = false;
      } else if (!strcmp(argv[i], GNU_delete_empty_line)) {
        flags->is_delete_empty_line = true;
      } else {
        return argv[i];
      }
    } else {
      files[(*file_count)++] = argv[i];
    }
  }
  return NULL;
}
