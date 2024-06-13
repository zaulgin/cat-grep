#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Недостаточно аргументов\n");
    return 0;
  }
  regex_t regex;
  int result;
  result = regcomp(&regex, argv[1], REG_EXTENDED);
  if (result) {
    printf("ERROR");
    return 0;
  }

  FILE *f = fopen("regex.txt", "r");
  if (f == NULL) {
    printf("Нет такого файла или каталога\n");
    return 0;
  }

  char buf[100];
  while (fgets(buf, 100, f)) {
    result = regexec(&regex, buf, 0, NULL, 0);
    if (!result) {
      printf("%s", buf);
    }
  }
  regfree(&regex);
}