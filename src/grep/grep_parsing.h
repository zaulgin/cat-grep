#include "grep_functions.h"

#ifndef GREP_PARSING_H
#define GREP_PARSING_H

char parse_args(int argc, char *argv[], Option *o, char *files[], int *file_c,
                Pattern *p);
char handle_flag(char flag, char next_char, Option *o, Pattern *p,
                 char *next_arg);
void handle_pattern_file(const char *filename, Pattern *p);
void add_pattern(Pattern *p, const char *pattern);

#endif
