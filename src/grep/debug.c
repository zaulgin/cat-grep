#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Недостаточно аргументов\n");
        return 0;
    }

    // создаем экземпляр структуры regex_t
    regex_t regex;

    // переменная для результата компиляции и результата поиска регулярного выражения
    int result;

    /*regcomp - для компиляции регулярки, если не компилится- крашим.
      REG_EXTENDED - расширенный набор регулярок*/
    result = regcomp(&regex, argv[1], REG_EXTENDED);

    // любой отличный от 0 результат при компиляции - это ошибка
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
        /*regexec - как я понял, для поиска по регулярке, 1-й аргумент - сама структура,
          2-й аргумент - строка в которой ищем, остальные хз ;D*/
        result = regexec(&regex, buf, 0, NULL, 0);

        // логика такая же как у regcomp - 0 значит есть вхождение регулярки в строку
        if (!result) {
            printf("%s", buf);
        }
    }
    regfree(&regex);
}
