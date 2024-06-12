#include "grep_functions.h"

void output(char *files[], Grep_flags *flags, int file_count, char *pattern) {
    char buf[1000];
    char buf_output[1000];
    int count_rows;

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            printf("%s: Нет такого файла или каталога\n", files[i]);
            continue;
        }

        count_rows = 0;

        while (fgets(buf, 1000, f)) {
            strcpy(buf_output, buf);

            if (flags->is_ignore_register) {
                pattern = str_lower(pattern);
                str_lower(buf);
            }

            if (!strstr(buf, pattern)) {
                continue;
            }

            if (flags->is_count_rows) {
                count_rows++;
            } else {
                printf("%s", buf_output);
            }
        }

        if (flags->is_count_rows) {
            printf("%d", count_rows);
        }

        fclose(f);
    }
}

char *str_lower(char *string) {
    unsigned char *p = (unsigned char *)string;
    while (*p) {
        *p = tolower(*p);
        p++;
    }
    return string;
}