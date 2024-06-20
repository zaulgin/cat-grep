#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char files[][26] = {"src_test/english_test.txt", "src_test/russian_test.txt",
                      "src_test/symbols_test.txt"};
  char patterns[][15] = {"@",    "АМЕРИКИ", "are",     "WiNdoW",
                         "Согл", "'[0-9]'", "'[d-e]'", "'[а-б]'"};
  char options[][2] = {"i", "v", "s", "c", "n", "h", "o", "l"};

  char flags_str[30] = "";
  char files_str[400] = "";
  char patterns_str[400] = "";

  char output_grep[1000];
  char output_s21_grep[1000];

  for (int i = 0; i < 8; i++) {
    strcat(flags_str, options[i]);

    for (int k = 0; k < 8; k++) {
      strcat(patterns_str, " -e ");
      strcat(patterns_str, patterns[k]);

      for (int j = 0; j < 3; j++) {
        strcat(files_str, " ");
        strcat(files_str, files[j]);

        snprintf(output_grep, sizeof(output_grep),
                 "grep -%s%s%s -f src_test/patterns.txt >> log_grep.log",
                 flags_str, patterns_str, files_str);
        snprintf(
            output_s21_grep, sizeof(output_s21_grep),
            "./s21_grep -%s%s%s -f src_test/patterns.txt >> log_s21_grep.log",
            flags_str, patterns_str, files_str);

        system(output_grep);
        system(output_s21_grep);

        printf("%s\n", output_grep);
        printf("%s\n", output_s21_grep);
      }
      memset(files_str, 0, sizeof(files_str));
    }
    memset(patterns_str, 0, sizeof(patterns_str));
  }

  system("diff log_grep.log log_s21_grep.log > changes.diff");
  FILE *f = fopen("changes.diff", "r");
  char res[2000];
  if (fgets(res, sizeof(res), f)) {
    printf("TEST FAILED\n");
  } else {
    printf("TEST SUCCESS\n");
  }

  fclose(f);
  return 0;
}
