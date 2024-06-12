#include "grep_functions.h"

void output(char *files[], Grep_flags *flags, int file_count, char *pattern) {
    bool output_var;  // переменная для флага -v
    char buf[1000];
    char buf_output[1000];
    int count_rows;
    char *filename = "";

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            if (!flags->is_file_error_ignore) {  // флаг -s - не выводит сообщение об ошибке если true
                printf("%s: Нет такого файла или каталога\n", files[i]);
            }
            continue;
        }
        
        if (flags->many_files) {
            filename = strcat(files[i], ":");
        }

        count_rows = 0;

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

            if (flags->is_count_rows) {  // флаг -c выводит колво строк
                if (output_var) {
                    count_rows++;
                }
            } else {
                if (output_var) {
                    printf("%s%s", filename, buf_output);
                }
            }
        }

        if (flags->is_count_rows) {
            printf("%s%d\n", filename, count_rows);
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