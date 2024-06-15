#include "parsing_grep.h"

// TODO с учетом массива флагов, переделать функцию парсинга: возможно вывести
// инициализацию флагов в отдельную функцию
char *parse_args(int argc, char *argv[], Grep_flags *flags, Grep_behavior *behavior, char *files[],
                 int *file_count, char *patterns[], int *pattern_c) {
    bool skip_next_arg = false;
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
                    case 'f':
                        // printf("zashel v -f\n");
                        flags->is_pattern_file = true;
                        FILE *f = fopen(argv[i + 1], "r");
                        char *buf = malloc(100);
                        while (fgets(buf, 100, f)) {
                            int last_symb = (int)strlen(buf) - 1;
                            if (buf[last_symb] == '\n') {
                                buf[last_symb] = '\0';
                            }
                            // printf("buf = %s\n", buf);
                            patterns[(*pattern_c)++] = buf;
                            printf("4ek patterna iz faila = %s\n", patterns[(*pattern_c) - 1]);
                        }
                        fclose(f);
                        skip_next_arg = true;
                        break;
                    case 'e':
                        // printf("zashel v -e\n");
                        flags->is_many_patterns = true;
                        if (i == argc - 1) {
                            return "oshibka -e";
                        }
                        patterns[(*pattern_c)++] = argv[i + 1];
                        skip_next_arg = true;
                        break;
                    default:
                        return argv[i];
                }
            }
            if (skip_next_arg) {
                // printf("zashel v skip\n");
                i++;
                skip_next_arg = false;
            }
        } else if (argv[i][0] != '-' && !behavior->is_single_pattern && !flags->is_many_patterns) {
            behavior->is_single_pattern = true;
            patterns[(*pattern_c)++] = argv[i];
        } else {
            files[(*file_count)++] = argv[i];
        }
    }
    if (*file_count > 1) {
        behavior->many_files = true;
    }

    // if (flags->is_register_ignore) {
    //     regcomp(regex, pattern, REG_ICASE);
    // } else {
    //     regcomp(regex, pattern, 0);
    // }

    for (int i = 0; i < *pattern_c; i++) {
        printf("паттерн №%d = %s\n", i, patterns[i]);
    }

    for (int i = 0; i < *file_count; i++) {
        printf("файл №%d = %s\n", i, files[i]);
    }

    return NULL;
}