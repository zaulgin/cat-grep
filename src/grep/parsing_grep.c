#include "parsing_grep.h"

// TODO с учетом массива флагов, переделать функцию парсинга: возможно вывести
// инициализацию флагов в отдельную функцию
char *parse_args(int argc, char *argv[], Grep_flags *flags, char *files[], int *file_count, char **pattern) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'i') {
                flags->is_ignore_register = true;
            } else {
                return argv[i];
            }
        } else if (argv[i][0] != '-' && !flags->is_pattern) {
            flags->is_pattern = true;
            *pattern = argv[i];
        } else {
            files[(*file_count)++] = argv[i];
        }
    }
    return NULL;
}