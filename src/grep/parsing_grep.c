#include "parsing_grep.h"

// TODO с учетом массива флагов, переделать функцию парсинга: возможно вывести
// инициализацию флагов в отдельную функцию
char *parse_args(int argc, char *argv[], Grep_flags *flags, char *files[], int *file_count, char **pattern) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '-') {
            for (int j = 1; j < (int)strlen(argv[i]); j++) {
                switch (argv[i][j]) {
                    case 'i':
                        flags->is_register_ignore = true;
                        break;
                    case 'v':
                        flags->is_invert_results = true;
                        break;
                    case 's':
                        flags->is_file_error_ignore = true;
                        break;
                    default:
                        return argv[i];
                }
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