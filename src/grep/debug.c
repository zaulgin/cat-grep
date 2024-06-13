#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Недостаточно аргументов\n");
    return 0;
  }
  
  regex_t regex; //создаем экземпляр структуры regex_t
  int result; //переменная для результата компиляции и поиска регулярного выражения
  result = regcomp(&regex, argv[1], REG_EXTENDED); //regcomp - для компиляции регулярки, если не компилится - крашим. REG_EXTENDED - расширенный набор регулярок
  if (result) { //любой отличный от 0 результат при компиляции - это ошибка
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
    result = regexec(&regex, buf, 0, NULL, 0); //regexec - как я понял, для поиска по регулярке, 1-й аргумент - сама структура, 2-й аргумент - строка в которой ищем, остальные хз ;D
    if (!result) { //логика такая же как у regcomp - 0 значит есть вхождение регулярки в строку
      printf("%s", buf);
    }
  }
  regfree(&regex);
}
