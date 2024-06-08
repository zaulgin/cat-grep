#include "cat_functions.h"

void print_files(char *files[], Cat_flags *flags, int file_count) {
    int row_count = 1;
    char buf[2000];

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            printf("%s: Нет такого файла или каталога\n", files[i]);
            continue;
        }

        static bool empty_line = false;
        static bool prev_empty_line = false;

        while (fgets(buf, 2000, f)) {
            check_empty_lines(&empty_line, &prev_empty_line, buf);

            if (flags->is_delete_empty_line && empty_line && prev_empty_line) {
                continue;
            }

            if (flags->is_all_line_numbers) {
                printf("    %d  ", row_count);
                row_count++;
            }

            if (flags->is_non_empty_line_numbers) {
                if (buf[0] != '\0' && buf[0] != '\n') {
                    printf("    %d  ", row_count);
                    row_count++;
                }
            }

            if (flags->is_end_of_string) {
                dollar_end_of_string(buf);
            }

            if (flags->is_nonprinting_chars) {
                nonprinting_chars(buf);
            }

            if (flags->is_tabs) {
                tab_change(buf);
            }

            printf("%s", buf);
        }
        fclose(f);
    }
}

void check_empty_lines(bool *empty_line, bool *prev_empty_line, char buf[]) {
    if (buf[0] == '\n' || buf[0] == '\0') {
        if (*empty_line) {
            *prev_empty_line = true;
        }
        *empty_line = true;
    } else {
        *empty_line = false;
        *prev_empty_line = false;
    }
}

//ДОРАБОТАТЬ! НЕВЕРНО ОБРАБАТЫВАЕТ СПЕЦ.СИМВОЛ!!!! УСЛОВИЕ НЕВЕРНОЕ!
void nonprinting_chars(char buf[]) {
    for (int i = 0; i < (int)strlen(buf); i++) {
        unsigned char uc = buf[i];
        if (uc >= 127) {
            if (uc == 127) {
                for (int j = (int)strlen(buf) + 2; j > i + 1; j--) {
                    buf[j] = buf[j - 1];
                }
                buf[i] = '^';
                buf[i + 1] = '?';
                continue;
            }
            uc = uc & 127;
            if (uc < 32) {
                for (int j = (int)strlen(buf) + 4; j > i + 3; j--) {
                    buf[j] = buf[j - 3];
                }
                buf[i + 3] = (uc & 127) + 64;
                buf[i + 2] = '^';
                buf[i + 1] = '-';
                buf[i] = 'M';
            } else {
                for (int j = (int)strlen(buf) + 3; j > i + 2; j--) {
                    buf[j] = buf[j - 2];
                }
                buf[i + 1] = '-';
                buf[i + 2] = uc & 127;
                buf[i] = 'M';
            }
        }
    }
}

void tab_change(char buf[]) {
    for (int i = 0; i < (int)strlen(buf); i++) {
        if (buf[i] == '\t') {
            for (int j = (int)strlen(buf) + 2; j > i + 1; j--) {
                buf[j] = buf[j - 1];
            }
            buf[i] = '^';
            buf[i + 1] = 'I';
        }
    }
}

void dollar_end_of_string(char buf[]) {
    char *d = strchr(buf, '\n');
    *d = '$';
    strcat(buf, "\n");
}