#include "grep_functions.h"

#ifndef PARSING_GREP_H
#define PARSING_GREP_H

char parse_args(int argc, char *argv[], Option *o, char *files[], int *file_c,
                Pattern *p);
char handle_flag(char flag, char next_char, Option *o, Pattern *p,
                 char *next_arg);
void handle_pattern_file(char *filename, Pattern *p);

#endif
