#include <stdio.h>
#include <string.h>

#include "cat_struct.h"

#ifndef CAT_FUNCTIONS_H
#define CAT_FUNCTIONS_H

void print_files(char *files[], Cat_flags *flags, int file_count);
void print_line_number(int *row_count);

#endif
