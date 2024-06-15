#include "grep_functions.h"

bool *reg_handle(int pattern_c, char *patterns[], regex_t *regex, int regcomp_val) {
    int res_regcomp;
    bool res_reg_handle;
    for (int i = 0; i < pattern_c; i++) {
        res_regcomp = regcomp(&regex, patterns[i], regcomp_val);
        if (res_regcomp) {
            printf("Ошибка компиляции рег. выражения");
            return NULL;
        }
        if (regexec(&regex, buf, 0, NULL, 0)) {
            var_output = true;
        }
    }
}

void output(char *files[], Grep_flags flags, Grep_behavior behavior, int file_count, regex_t regex,
            char *patterns[], int pattern_c) {
    int regcomp_val = 0;

    if (flags.is_register_ignore) {
        regcomp_val = REG_ICASE;
    }

    if (file_count > 1 && !flags.is_filename_ignore) {
        behavior.many_files = true;
    }

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            if (!flags.is_file_error_ignore) {  // флаг -s - не выводит сообщение об
                                                // ошибке если true
                printf("%s: Нет такого файла или каталога\n", files[i]);
            }
            continue;
        }
        char prefix[1000] = "";
        if (behavior.many_files) {
            strcat(prefix, files[i]);
            strcat(prefix, ":");
        }
        // флаг, чтобы избежать повторного вывода имени файла
        print_grep(flags, prefix, patterns, pattern_c, regex, regcomp_val, f, files[i]);
        // fclose(f);
    }
}

void print_grep(Grep_flags flags, char prefix[], char *patterns[], int pattern_c, regex_t regex,
                int regcomp_val, FILE *f, char filename[]) {
    int count_rows = 0;
    int row_num = 0;
    bool var_output = false;
    bool file_printed = false;
    char buf[1000];

    int res_regcomp;
    int res_regexec;
    while (fgets(buf, 1000, f)) {
        delete_new_line(buf);

        row_num++;

        if (flags.is_invert_results) {  // флаг -v - инвертирует результаты
            var_output = !var_output;
        }

        if (var_output) {
            if (flags.is_only_filename) {  // флаг -l выводит имя файла
                printf("%s\n", filename);
                file_printed = true;
                break;
            }
            if (flags.is_count_rows) {  // флаг -c выводит кол-во строк
                count_rows++;
            } else {
                if (flags.is_num_row) {
                    char temp[12];
                    sprintf(temp, "%d", row_num);
                    strcat(prefix, temp);
                    strcat(prefix, ":");
                }
                printf("%s%s\n", prefix, buf);
            }
        }
        strcpy(prefix, "");
        strcat(prefix, filename);
        strcat(prefix, ":");
        var_output = false;
    }

    if (file_printed) {
        fclose(f);
        return;
    }

    if (flags.is_count_rows) {
        strcat(prefix, filename);
        strcat(prefix, ":");
        printf("%s%d\n", prefix, count_rows);
    }
}

void delete_new_line(char buf[]) {
    int last_symb = (int)strlen(buf) - 1;
    if (buf[last_symb] == '\n') {
        buf[last_symb] = '\0';
    }
}
