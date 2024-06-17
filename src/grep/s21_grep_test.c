#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // char patterns[] = "src_test/patterns.txt";
  char files[][26] = {"src_test/english_test.txt", "src_test/russian_test.txt",
                      "src_test/symbols_test.txt"};
  // char minus[] = "-";
  char options[][2] = {"i",
                       "v",
                       "s",
                       "c"
                       "n",
                       "l",
                       "h",
                       "o"};
  // char options_for_patterns[][2] = {"e", "f"};
  char grep[] = "grep";
  char s21_grep[] = "./s21_grep";
  bool is_single_pattern = false;

  char out_grep[1000];
  char out_s21_grep[1000];

  for (int i = 0; i < 8; i++) {
    strcpy(out_grep, grep);
    strcpy(out_s21_grep, s21_grep);

    strcat(out_grep, "-");
    strcat(out_s21_grep, "-");

    strcat(out_grep, options[i]);
    strcat(out_s21_grep, options[i]);
    if (!is_single_pattern) {
      strcat(out_grep, " are ");
      strcat(out_s21_grep, " are ");
      is_single_pattern = true;
    }
    for (int j = 0; j < 3; j++) {
      strcat(out_grep, files[j]);
      strcat(out_s21_grep, files[j]);
      printf("%s >> log_grep.txt\n", out_grep);
      printf("%s >> log_s21_grep.txt", out_s21_grep);
    }
  }

  char res[2000];
  system("diff log_grep.txt log_s21_grep.txt > changes.diff");
  FILE *g = fopen("changes.diff", "r");
  if (fgets(res, sizeof(res), g)) {
    printf("TEST FAILED\n");
  } else
    printf("TEST SUCCESS\n");

  fclose(g);
  return 0;
}