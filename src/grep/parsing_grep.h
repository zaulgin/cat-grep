#include "grep_functions.h"

#ifndef PARSING_GREP_H
#define PARSING_GREP_H

char *parse_args(int argc, char *argv[], Grep_flags *flags, char *files[], int *file_count, char **pattern);

#endif
