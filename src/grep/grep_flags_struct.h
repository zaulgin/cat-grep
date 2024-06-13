#include <stdbool.h>
#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

typedef struct {
    bool is_register_ignore;  // игнорирует регистр
    bool is_invert_results;   // инвертирует смысл поиска
    bool is_file_error_ignore;  // подавляет сообщения об ошибках несуществующего файла
    bool is_count_rows;  // выводит количество найденных свопадений в строках
    bool is_num_row; //выводит номер строки в файле
    bool is_only_filename;  //выводит только наименование файла

} Grep_flags;

typedef struct {
    bool many_files; // количество файлов больше 1
    bool is_pattern;          // флаг шаблона
} Grep_behavior;

#endif