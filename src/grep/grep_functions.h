#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep_flags_struct.h"

#ifndef GREP_FUNCTIONS_H
#define GREP_FUNCTIONS_H

void output(char *files[], Grep_flags flags, Grep_behavior behavior, int file_count, regex_t regex);
char *str_lower(char *string);

#endif
