#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "grep_flags_struct.h"

#ifndef GREP_FUNCTIONS_H
#define GREP_FUNCTIONS_H

void output(char *files[], Grep_flags *flags, int file_count, char *pattern);
char *str_lower(char *string);

#endif
