#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep_struct.h"

#ifndef GREP_FUNCTIONS_H
#define GREP_FUNCTIONS_H

void handler(char *files[], Option o, bool many_files, int file_c, Pattern *p);
void delete_new_line(char buf[]);
void print_string(Option o, char prefix[], Pattern *p, int regcomp_val,
                  FILE *fstream);
void print_matches(Option o, char prefix[], Pattern *p, int regcomp_val,
                   FILE *fstream);
void print_filename(Option o, Pattern *p, int regcomp_val, FILE *fstream,
                    char *filename);
void print_match_c(Option o, char prefix[], Pattern *p, int regcomp_val,
                   FILE *fstream);
bool reg_handler(Pattern *p, int regcomp_val, char buf[],
                 bool is_invert_results);
void free_strings(int count, char *string[]);

#endif
