#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep_flags_struct.h"

#ifndef GREP_FUNCTIONS_H
#define GREP_FUNCTIONS_H

void output(char *files[], Grep_flags flags, Grep_behavior behavior, int file_c, regex_t regex,
            char *patterns[], int pattern_c);
void delete_new_line(char buf[]);
void print_grep(Grep_flags flags, char prefix[], char *patterns[], int pattern_c, regex_t regex,
                int regcomp_val, FILE *f, char filename[]);
bool reg_handle(int pattern_c, char *patterns[], regex_t *regex, int regcomp_val, char buf[]);
int regexec_result(regex_t *regex, char buf[]);
void free_string(int count, char *string[]);

#endif
