#include "cat_functions.h"

#ifndef CAT_PARSING_H
#define CAT_PARSING_H

char *parse_args(int argc, char *argv[], Cat_flags *flags, char *files[],
                 int *file_count);

#endif
