#include "grep_functions.h"

#ifndef PARSING_GREP_H
#define PARSING_GREP_H

char *parse_args(int argc, char *argv[], Grep_flags *flags, Grep_behavior *behavior, char *files[],
                 int *file_count, regex_t *regex);

#endif
