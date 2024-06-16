/*
сделать проверку cpp check
сделать проверку valgrind
*/

#include <regex.h>
#include <stdlib.h>

#include "parsing_grep.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Недостаточно аргументов\n");
    exit(1);
  }

  char *files[argc];
  int file_c = 0;

  Pattern patterns = {0};
  Option options = {false, false, false, false, false,
                    false, false, false, false};
  bool many_files = false;

  char error_parse_args =
      parse_args(argc, argv, &options, files, &file_c, &patterns);
  if (error_parse_args != 0) {
    fprintf(stderr, "Неверный ключ %c", error_parse_args);
    exit(1);
  }

  handler(files, options, many_files, file_c, &patterns);

  free_string(patterns.count, patterns.val);
  return 0;
}