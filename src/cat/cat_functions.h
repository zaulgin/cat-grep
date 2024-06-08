#include <stdio.h>
#include <string.h>

#include "cat_flags_struct.h"

#ifndef CAT_FUNCTIONS_H
#define CAT_FUNCTIONS_H

void print_files(char *files[], Cat_flags *flags, int file_count);
void dollar_end_of_string(char buf[]);
void tab_change(char buf[]);
void check_empty_lines(bool *empty_line, bool *prev_empty_line, char buf[]);
void nonprinting_chars(char buf[]);

#endif
