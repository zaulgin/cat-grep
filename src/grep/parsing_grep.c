#include "parsing_grep.h"

// TODO с учетом массива флагов, переделать функцию парсинга: возможно вывести
// инициализацию флагов в отдельную функцию
char *parse_args(int argc, char *argv[], Grep_flags *flags, Grep_behavior *behavior, char *files[],
                 int *file_count, regex_t *regex) {
    char *pattern = (char *)malloc(100);
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
                    case 'c':
                        flags->is_count_rows = true;
                        break;
                    case 'n':
                        flags->is_num_row = true;
                        break;
                    case 'l':
                        flags->is_only_filename = true;
                        break;
                    default:
                        return argv[i];
                }
            }
        } else if (argv[i][0] != '-' && !behavior->is_pattern) {
            behavior->is_pattern = true;
            pattern = argv[i];
        } else {
            files[(*file_count)++] = argv[i];
        }
    }
    if (*file_count > 1) {
        behavior->many_files = true;
    }
    if (flags->is_register_ignore) {
        regcomp(regex, pattern, REG_ICASE);
    } else {
        regcomp(regex, pattern, REG_EXTENDED);
    }
    return NULL;
}