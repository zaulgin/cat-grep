#include "grep_functions.h"

void output(char *files[], Grep_flags *flags, int file_count, char *pattern) {
    bool output_var;  // переменная для флага -v
    char buf[1000];
    char buf_output[1000];

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            if (!flags->is_file_error_ignore) {  // флаг -s - не выводит сообщение об ошибке если true
                printf("%s: Нет такого файла или каталога\n", files[i]);
            }
            continue;
        }

        while (fgets(buf, 1000, f)) {
            strcpy(buf_output, buf);

            if (flags->is_register_ignore) {  // флаг -i - игнорит регистр
                pattern = str_lower(pattern);
                str_lower(buf);
            }

            output_var = strstr(buf, pattern);

            if (flags->is_invert_results) {  // флаг -v - инвертирует результаты
                output_var = !output_var;
            }

            if (output_var) {
                printf("%s", buf_output);
            }
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