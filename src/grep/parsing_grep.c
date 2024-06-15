#include "parsing_grep.h"

char *parse_args(int argc, char *argv[], Grep_flags *flags, Grep_behavior *behavior, char *files[],
                 int *file_count, char *patterns[], int *pattern_c) {
    bool skip_next_arg = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && (int)strlen(argv[i]) > 1) {
            for (int j = 1; j < (int)strlen(argv[i]); j++) {
                char res = handle_flag(argv[i][j], flags, patterns, pattern_c,
                                       (i + 1 < argc) ? argv[i + 1] : NULL, &skip_next_arg);
                if (res != 0) {
                    return "Ошибочный флаг\n";
                }
            }
            if (skip_next_arg) {
                i++;
                skip_next_arg = false;
            }
        } else if (!behavior->is_single_pattern && !flags->is_many_patterns) {
            behavior->is_single_pattern = true;
            patterns[(*pattern_c)++] = argv[i];
        } else {
            files[(*file_count)++] = argv[i];
        }
    }

    return NULL;
}

char handle_flag(char flag, Grep_flags *flags, char *patterns[], int *pattern_c, char *next_arg,
                 bool *skip_next_arg) {
    switch (flag) {
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
            flags->is_pattern_file = true;
            handle_pattern_file(next_arg, patterns, pattern_c);
            *skip_next_arg = true;
            break;
        case 'h':
            flags->is_filename_ignore = true;
            break;
        case 'e':
            flags->is_many_patterns = true;
            patterns[(*pattern_c)++] = next_arg;
            *skip_next_arg = true;
            break;
        default:
            return flag;
    }
    return 0;
}

void handle_pattern_file(char *filename, char *patterns[], int *pattern_c) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("%s: Нет такого файла или каталога\n", filename);
        return;
    }
    char buf[100];
    while (fgets(buf, sizeof(buf), f)) {
        delete_new_line(buf);
        patterns[(*pattern_c)++] = buf;
    }
    fclose(f);
}