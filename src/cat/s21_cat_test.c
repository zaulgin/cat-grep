#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char files[][20] = {"src_test/test1.txt", "src_test/test2.txt",
                      "src_test/test3.txt"};
  char options[][2] = {"A", "t", "T", "e", "E", "s", "n", "b", "v"};
  char gnu_options[][18] = {"--number-nonblank", "--number", "--squeeze-blank"};

  char flags_str[100] = "";
  char files_str[400] = "";
  char gnu_flags_str[300] = "";
  char output_cat[1000];
  char output_s21_cat[1000];

  for (int i = 0; i < 9; i++) {
    strcat(flags_str, options[i]);

    for (int k = 0; k < 3; k++) {
      strcat(gnu_flags_str, " ");
      strcat(gnu_flags_str, gnu_options[k]);

      for (int j = 0; j < 3; j++) {
        strcat(files_str, " ");
        strcat(files_str, files[j]);

        snprintf(output_cat, sizeof(output_cat), "cat -%s%s%s >> log_grep.log",
                 flags_str, gnu_flags_str, files_str);
        snprintf(output_s21_cat, sizeof(output_s21_cat),
                 "./s21_cat -%s%s%s >> log_s21_grep.log", flags_str,
                 gnu_flags_str, files_str);

        system(output_cat);
        system(output_s21_cat);

        printf("  %s\n", output_cat);
        printf("  %s\n", output_s21_cat);
      }

      memset(files_str, 0, sizeof(files_str));
    }

    memset(gnu_flags_str, 0, sizeof(gnu_flags_str));
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
