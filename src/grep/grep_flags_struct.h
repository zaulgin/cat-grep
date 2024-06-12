#include <stdbool.h>
#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

typedef struct {
    bool is_pattern;          // флаг шаблона
    bool is_register_ignore;  // нумерует непустые строки
    bool is_invert_results;   // инвертирует смысл поиска
    bool is_file_error_ignore;  // подавляет сообщения об ошибках несуществующего файла
} Grep_flags;

#endif