#include <regex.h>
#include <stdbool.h>

#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

typedef struct {
  bool is_register_ignore;  // -i игнорирует регистр
  bool is_invert_results;   // -v инвертирует смысл поиска
  bool is_file_error_ignore;  // -s подавляет сообщения об ошибках
                              // несуществующего файла
  bool is_match_count;  // -c выводит количество найденных свопадений в строках
  bool is_num_row;  // -n выводит номер строки в файле
  bool is_only_filename;  // -l выводит только наименование файла
  bool is_pattern;  // есть паттерн
  bool is_filename_ignore;  // -h не выводит имена файлов если их больше 1
  bool is_only_match;  // -o печатает только совпадающие (непустые) части
                       // совпавшей строки.
} Option;

typedef struct {
  char *val[1000];
  int count;
} Pattern;

#endif