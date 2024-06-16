#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buff[1000], buff2[1000];
    char res_cat[1000];
    char res_s21_cat[1000];
    char tmp[1000], tmp2[1000];
    FILE *f = fopen("combination_flags.txt", "r");
    if (f == NULL) {
        printf("Нет такого файла или каталога\n");
        return 1;
    }
    FILE *f_files = fopen("combination_files.txt", "r");
    if (f_files == NULL) {
        printf("Нет такого файла или каталога\n");
        return 1;
    }

    for (int i = 0; i < 91; i++) {
        fgets(buff, 1000, f);
        strcpy(res_cat, "cat ");
        strcpy(res_s21_cat, "../s21_cat ");
        buff[strcspn(buff, "\n")] = ' ';
        strcat(res_cat, buff);
        strcat(res_s21_cat, buff);

        for (int i = 0; i < 7; i++) {
            printf("\n");

            FILE *f_files = fopen("combination_files.txt", "r");
            while (fgets(buff2, 1000, f_files) != NULL) {
                strcpy(tmp, res_cat);
                buff2[strcspn(buff2, "\n")] = ' ';
                strcat(tmp, buff2);

                strcat(tmp, ">> log_cat.txt\n");

                printf("%s", tmp);
                system(tmp);
            }
            fclose(f_files);
            FILE *f_files2 = fopen("combination_files.txt", "r");
            while (fgets(buff2, 1000, f_files) != NULL) {
                strcpy(tmp2, res_s21_cat);
                buff2[strcspn(buff2, "\n")] = ' ';
                strcat(tmp2, buff2);

                strcat(tmp2, ">> log_s21_cat.txt\n");

                printf("%s", tmp2);
                system(tmp2);
            }
            fclose(f_files2);
        }
    }
    fclose(f);

    //сравниваю через diff два файла. Команда diff служит для сравнения текстовых файлов. 
    //результат сравнения пишу в файл test/changes.diff
    //при несовпадении выводит текст TEST FAILED
    char res[1000];
    system("diff log_cat.txt log_s21_cat.txt > changes.diff");
    FILE *g = fopen("changes.diff", "r");
    if(fgets(res, 1000, g) != NULL){
        printf("TEST FAILED\n");
    } else printf("TEST SUCCESS\n");

    fclose(g);
    

    

    return 0;
}