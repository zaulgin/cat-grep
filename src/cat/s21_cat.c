#include "parsing.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Недостаточно аргументов\n");
        return 0;
    }

    const char *files[argc];
    int file_count = 0;
    Cat_flags flags = {false, false, false, false, false, false};

    char *error_parse_args = parse_args(argc, argv, &flags, files, &file_count);
    if (error_parse_args != NULL) {
        printf("Неверный ключ %s", error_parse_args);
        return 1;
    }

    print_files(files, &flags, file_count);

    return 0;
}