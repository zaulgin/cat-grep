#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *add_log(char string[], char log_message[]) {
//   char *log = malloc(1000);
//   strcat(log, string);
//   strcat(log, log_message);
//   return log;
// }

// char *add_file(char string[], char filename[]) {
//   char *file = malloc(1000);
//   strcat(file, string);
//   strcat(file, " ");
//   strcat(file, filename);
//   return file;
// }

// char *add_pattern(char string[], char pattern_name[]) {
//   char *pattern = malloc(1000);
//   strcat(pattern, string);
//   strcat(pattern, " -e ");
//   strcat(pattern, pattern_name);
//   return pattern;
// }

int main() {
  char files[][26] = {"src_test/english_test.txt", "src_test/russian_test.txt",
                      "src_test/symbols_test.txt"};
  char pattern_file[] = "src_test/patterns.txt";
  char patterns[][20] = {"ам",
                         "АМЕРИКИ",
                         "are",
                         "WiNdoW",
                         "Согл",
                         "[0-9]",
                         "[d-e]",
                         "[а-б]"
                         "1",
                         "@"};
  char options[][2] = {"i",
                       "v",
                       "s",
                       "c"
                       "n",
                       "l",
                       "h",
                       "o"};
  // char options_for_patterns[][2] = {"e", "f"};
  char grep[] = "grep -";
  char s21_grep[] = "./s21_grep -";

  char out_grep[1000];
  char out_s21_grep[1000];
  strcpy(out_grep, grep);
  strcpy(out_s21_grep, s21_grep);
  char with_files_grep[1000];
  char with_files_s21_grep[1000];

  char with_pattern_grep[1000];
  char with_pattern_s21_grep[1000];

  char *output_grep = malloc(10000);
  char *output_s21_grep = malloc(10000);
  // без -f
  for (int i = 0; i < 8; i++) {
    strcat(out_grep, options[i]);
    strcat(out_s21_grep, options[i]);
    strcpy(with_pattern_grep, "");
    strcpy(with_pattern_s21_grep, "");
    for (int k = 0; k < 10; k++) {
      strcat(with_pattern_grep, " -e ");
      strcat(with_pattern_s21_grep, " -e ");
      strcat(with_pattern_grep, patterns[k]);
      strcat(with_pattern_s21_grep, patterns[k]);
      for (int j = 0; j < 3; j++) {
        strcat(with_files_grep, " ");
        strcat(with_files_s21_grep, " ");
        strcat(with_files_grep, files[j]);
        strcat(with_files_s21_grep, files[j]);
        output_grep = malloc(10000);
        output_s21_grep = malloc(10000);
        sprintf(output_grep, "%s%s%s >> log_grep.log", out_grep,
                with_pattern_grep, with_files_grep);
        sprintf(output_s21_grep, "%s%s%s >> log_s21_grep.log", out_s21_grep,
                with_pattern_s21_grep, with_files_s21_grep);
        system(output_grep);
        system(output_s21_grep);
        free(output_grep);
        free(output_s21_grep);
      }
    }

    strcpy(with_pattern_grep, "");
    strcpy(with_pattern_s21_grep, "");
    strcpy(with_files_grep, "");
    strcpy(with_files_s21_grep, "");
    strcpy(out_grep, grep);
    strcpy(out_s21_grep, s21_grep);

    char *output_grep = malloc(10000);
    char *output_s21_grep = malloc(10000);
    // с -f
    for (int i = 0; i < 8; i++) {
      strcat(out_grep, options[i]);
      strcat(out_s21_grep, options[i]);
      strcpy(with_pattern_grep, "");
      strcpy(with_pattern_s21_grep, "");
      strcat(with_pattern_grep, " -f ");
      strcat(with_pattern_s21_grep, " -f ");
      strcat(with_pattern_grep, pattern_file);
      strcat(with_pattern_s21_grep, pattern_file);
      for (int j = 0; j < 3; j++) {
        strcat(with_files_grep, " ");
        strcat(with_files_s21_grep, " ");
        strcat(with_files_grep, files[j]);
        strcat(with_files_s21_grep, files[j]);
        output_grep = malloc(10000);
        output_s21_grep = malloc(10000);
        sprintf(output_grep, "%s%s%s >> log_grep.log", out_grep,
                with_pattern_grep, with_files_grep);
        sprintf(output_s21_grep, "%s%s%s >> log_s21_grep.log", out_s21_grep,
                with_pattern_s21_grep, with_files_s21_grep);
        printf("%s\n", output_grep);
        printf("%s\n", output_s21_grep);
        system(output_grep);
        system(output_s21_grep);
        free(output_grep);
        free(output_s21_grep);
      }
    }

    char res[2000];
    system("diff log_grep.log log_s21_grep.log > changes.diff");
    FILE *g = fopen("changes.diff", "r");
    if (fgets(res, sizeof(res), g)) {
      printf("TEST FAILED\n");
    } else
      printf("TEST SUCCESS\n");

    fclose(g);
    return 0;
  }
}