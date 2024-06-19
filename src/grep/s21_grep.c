/*
сделать проверку cpp check
сделать проверку valgrind
*/
#include <locale.h>

#include "grep_parsing.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  if (argc < 3) {
    fprintf(stderr, "Недостаточно аргументов\n");
    exit(1);
  }

  char *files[argc];
  int file_c = 0;

  Pattern patterns = {NULL, 0, 0};
  Option options = {false, false, false, false, false,
                    false, false, false, false};

  char error_parse_args =
      parse_args(argc, argv, &options, files, &file_c, &patterns);
  if (error_parse_args != 0) {
    free_strings(patterns.count, patterns.val);
    free(patterns.val);
    fprintf(stderr, "Неверный ключ %c", error_parse_args);
    exit(1);
  }

  handler(files, options, file_c, &patterns);

  free_strings(patterns.count, patterns.val);
  free(patterns.val);

  return 0;
}