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
    Grep_flags flags = {false, false, false};

    char *error_parse_args = parse_args(argc, argv, &flags, files, &file_count, &pattern);
    if (error_parse_args != NULL) {
        printf("Неверный ключ %s", error_parse_args);
        return 1;
    }

    output(files, &flags, file_count, pattern);

    return 0;
}