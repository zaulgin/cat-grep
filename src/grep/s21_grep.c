/*
сделать проверку cpp check
сделать проверку valgrind
*/


#include <stdlib.h>

#include "parsing_grep.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Недостаточно аргументов\n");
        return 0;
    }

    char *files[argc];
    char *pattern = malloc(1000);

    int file_count = 0;
    Grep_flags flags = {false, false, false, false, false, false};
    Grep_behavior behavior = {false, false};

    char *error_parse_args = parse_args(argc, argv, &flags, &behavior, files, &file_count, &pattern);
    if (error_parse_args != NULL) {
        printf("Неверный ключ %s", error_parse_args);
        return 1;
    }

    output(files, flags, behavior, file_count, pattern);
    free(pattern);

    return 0;
}