#include "grep_functions.h"

#ifndef PARSING_GREP_H
#define PARSING_GREP_H

char *parse_args(int argc, char *argv[], Grep_flags *flags, Grep_behavior *behavior, char *files[],
                 int *file_count, char *patterns[], int *pattern_c);
char handle_flag(char flag, Grep_flags *flags, char *patterns[], int *pattern_c, char *next_arg,
                 bool *skip_next_arg);
void handle_pattern_file(char *filename, char *patterns[], int *pattern_c);

#endif
