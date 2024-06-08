#include <stdbool.h>
#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

// TODO флаги переделать, отдефайнить и запихать в статик массив стрингов
#define non_empty_line_numbers "-b"
#define end_of_string "-e"
#define all_line_numbers "-n"
#define delete_empty_line "-s"
#define tabs "-t"
#define non_printing "v"
#define GNU_non_empty_line_numbers "--number-nonblank"
#define GNU_all_line_numbers "--number"
#define GNU_delete_empty_line "--squeeze-blank"

typedef struct {
    bool is_non_empty_line_numbers;  // нумерует непустые строки
    bool is_end_of_string;           // отображение конца строки как $
    bool is_all_line_numbers;        // нумерует все строки
    bool is_delete_empty_line;       // удаление нескольких пустых строк
    bool is_tabs;                    // отображение tab как ^|
    bool is_nonprinting_chars;       // непечатные символы
} Cat_flags;

#endif