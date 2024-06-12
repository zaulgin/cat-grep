#include <stdbool.h>
#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

typedef struct {
    bool is_pattern;          // флаг шаблона
    bool is_ignore_register;  // нумерует непустые строки
} Grep_flags;

#endif