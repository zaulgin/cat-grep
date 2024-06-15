/*
сделать проверку cpp check
сделать проверку valgrind
*/

#include <regex.h>
#include <stdlib.h>

#include "parsing_grep.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Недостаточно аргументов\n");
        return 0;
    }

    regex_t regex;
    char *files[argc];
    char *patterns[1000];

    int file_count = 0;
    int pattern_c = 0;
    Grep_flags flags = {false, false, false, false, false, false, false, false, false, false};
    Grep_behavior behavior = {false, false};

    char *error_parse_args =
        parse_args(argc, argv, &flags, &behavior, files, &file_count, patterns, &pattern_c);
    if (error_parse_args != NULL) {
        printf("Неверный ключ %s", error_parse_args);
        return 1;
    }

    output(files, flags, behavior, file_count, regex, patterns, pattern_c);

    return 0;
}