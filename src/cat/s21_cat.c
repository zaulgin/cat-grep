#include <stdlib.h>

#include "cat_parsing.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Недостаточно аргументов\n");
    exit(1);
  }

  char *files[argc];

  int file_count = 0;
  Cat_flags flags = {false, false, false, false, false, false};

  char *error_parse_args = parse_args(argc, argv, &flags, files, &file_count);
  if (error_parse_args != NULL) {
    fprintf(stderr, "Неверный ключ %s", error_parse_args);
    exit(1);
  }

  print_files(files, &flags, file_count);

  return 0;
}