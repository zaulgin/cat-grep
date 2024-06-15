#include "cat_functions.h"
#include <string.h>

static void handle_delete_empty_lines(char ch, char *tmp_ch, int *empty_line_count, bool *skip);
static void handle_line_numbers(Cat_flags *flags, char tmp_ch, int *row_count);
static void handle_end_of_string(char ch);
static bool handle_tabs(char ch);
static bool handle_nonprinting_chars(char ch);

void print_files(char *files[], Cat_flags *flags, int file_count) {
    int row_count = 1;

    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(files[i], "r");
        if (f == NULL) {
            printf("%s: Нет такого файла или каталога\n", files[i]);
            continue;
        }

        char ch;
        char tmp_ch = 0;
        int empty_line_count = 0;

        while ((ch = fgetc(f)) != EOF) {
            bool skip = false;
            if (flags->is_delete_empty_line) {
                handle_delete_empty_lines(ch, &tmp_ch, &empty_line_count, &skip);
                if (skip) continue;
            }

            if (flags->is_all_line_numbers || flags->is_non_empty_line_numbers) {
                handle_line_numbers(flags, tmp_ch, &row_count);
            }

            if (flags->is_end_of_string) {
                handle_end_of_string(ch);
            }

            bool tabs_handled = false;
            if (flags->is_tabs) {
                tabs_handled = handle_tabs(ch);
            }

            bool nonprinting_handled = false;
            if (flags->is_nonprinting_chars) {
                nonprinting_handled = handle_nonprinting_chars(ch);
            }

            if (!tabs_handled && !nonprinting_handled) {
                fputc(ch, stdout);
            }

            tmp_ch = ch;
        }
        fclose(f);
    }
}

void print_line_number(int *row_count) {
    printf("%*d\t", 6, *row_count);
    (*row_count)++;
}

static void handle_delete_empty_lines(char ch, char *tmp_ch, int *empty_line_count, bool *skip) {
    if (*tmp_ch == '\n') {
        (*empty_line_count)++;
    } else {
        *empty_line_count = 0;
    }
    if (ch == '\n' && *empty_line_count > 1) {
        *tmp_ch = ch;
        *skip = true;
    } else {
        *skip = false;
    }
}

static void handle_line_numbers(Cat_flags *flags, char tmp_ch, int *row_count) {
    if ((flags->is_all_line_numbers && (tmp_ch == '\n' || *row_count == 1)) ||
        (flags->is_non_empty_line_numbers && ((tmp_ch == '\n' && tmp_ch != '\n') || *row_count == 1))) {
        print_line_number(row_count);
    }
}

static void handle_end_of_string(char ch) {
    if (ch == '\n') {
        fputc('$', stdout);
    }
}

static bool handle_tabs(char ch) {
    if (ch == '\t') {
        fputs("^I", stdout);
        return true;
    }
    return false;
}

static bool handle_nonprinting_chars(char ch) {
    if ((unsigned char)ch > 127) {
        char buf[] = {ch, 0};
        char uc;
        for (int i = 0; i < (int)strlen(buf); i++) {
            uc = (unsigned char)buf[i];
            uc = uc & 127;
            if (uc < 32) {
                printf("M-^%c", uc + 64);
            } else {
                printf("M-%c", uc);
            }
        }
        return true;
    } else if ((unsigned char)ch < 32 && ch != 9 && ch != 10 && ch != 12) {
        printf("^%c", ch + 64);
        return true;
    } else if (ch == 127) {
        printf("^?");
        return true;
    } else if (ch == 12) {
        printf("^L");
        return true;
    }
    return false;
}
