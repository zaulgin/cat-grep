#include "grep_functions.h"

void output(char *files[], Grep_flags flags, Grep_behavior behavior,int file_count, char *pattern) {
    bool output_var;  // переменная для флага -v
    char buf[1000];
    char buf_output[1000];
    int count_rows, row_num;
    char prefix[100] = "";

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            if (!flags.is_file_error_ignore) {  // флаг -s - не выводит сообщение об ошибке если true
                printf("%s: Нет такого файла или каталога\n", files[i]);
            }
            continue;
        }

        count_rows = 0;
        row_num = 0;

        while (fgets(buf, 1000, f)) {
            strcpy(buf_output, buf);
            row_num++;

            if (behavior.many_files) {
                strcat(prefix, files[i]);
                strcat(prefix, ":");
            }

            if (flags.is_register_ignore) {  // флаг -i - игнорит регистр
                pattern = str_lower(pattern);
                str_lower(buf);
            }

            output_var = strstr(buf, pattern);

            if (flags.is_invert_results) {  // флаг -v - инвертирует результаты
                output_var = !output_var;
            }

            if (flags.is_num_row) {
                char temp[10];
                itoa(row_num, temp, 10);
                strcat(prefix, temp);
                strcat(prefix, ":");
            }

            if (flags.is_count_rows) {  // флаг -c выводит колво строк
                if (output_var) {
                    count_rows++;
                }
            } else {
                if (output_var) {
                    printf("%s%s", prefix, buf_output);
                }
            }
            strcpy(prefix, "");
        }

        if (flags.is_count_rows) {
            strcat(prefix, files[i]);
            strcat(prefix, ":");
            printf("%s%d\n", prefix, count_rows);
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