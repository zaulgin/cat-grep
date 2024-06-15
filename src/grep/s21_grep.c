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

    int file_c = 0;
    int pattern_c = 0;
    Grep_flags flags = {false, false, false, false, false, false, false, false, false, false};
    Grep_behavior behavior = {false, false};

    char error_parse_args = parse_args(argc, argv, &flags, &behavior, files, &file_c, patterns, &pattern_c);
    if (error_parse_args != '\0') {
        printf("Неверный ключ %c", error_parse_args);
        return 0;
    }

    output(files, flags, behavior, file_c, regex, patterns, pattern_c);

    free_string(pattern_c, patterns);
    return 0;
}