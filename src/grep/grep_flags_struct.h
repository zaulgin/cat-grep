#include <regex.h>
#include <stdbool.h>

#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

typedef struct {
    bool is_register_ignore;  // -i игнорирует регистр
    bool is_invert_results;   // -v инвертирует смысл поиска
    bool is_file_error_ignore;  // -s подавляет сообщения об ошибках несуществующего файла
    bool is_count_rows;  // -c выводит количество найденных свопадений в строках
    bool is_num_row;          // -n выводит номер строки в файле
    bool is_only_filename;    // -l выводит только наименование файла
    bool is_pattern_file;     // -f берет паттерны из файла
    bool is_many_patterns;    // -e несколько паттернов
    bool is_filename_ignore;  // -h не выводит имена файлов если их больше 1
    bool is_only_match;  // -o печатает только совпадающие (непустые) части совпавшей строки.
} Grep_flags;

typedef struct {
    bool many_files;         // количество файлов больше 1
    bool is_single_pattern;  // единственный шаблон
} Grep_behavior;

#endif