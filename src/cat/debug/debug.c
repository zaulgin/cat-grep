#include <stdio.h>
#include <string.h>

int main() {
    char buf[1000] = "щ";

    // for (int i = 0; i < (int)strlen(buf); i++) {
    //     printf("%u ", (unsigned char)buf[i]);
    // }

    for (int i = 0; i < (int)strlen(buf); i++) {
        unsigned char uc = buf[i];
        if (uc >= 127) {
            if (uc == 127) {
                for (int j = (int)strlen(buf) + 2; j > i + 1; j--) {
                    buf[j] = buf[j - 1];
                }
                buf[i] = '^';
                buf[i + 1] = '?';
                continue;
            }
            uc = uc & 127;
            if (uc < 32) {
                // if (uc == 9 || uc == 10 || uc == 12) {
                //     continue;
                // }
                for (int j = (int)strlen(buf) + 4; j > i + 3; j--) {
                    buf[j] = buf[j - 3];
                }
                buf[i + 3] = (uc & 127) + 64;
                buf[i + 2] = '^';
                buf[i + 1] = '-';
                buf[i] = 'M';
            } else {
                for (int j = (int)strlen(buf) + 3; j > i + 2; j--) {
                    buf[j] = buf[j - 2];
                }
                buf[i + 1] = '-';
                buf[i + 2] = uc & 127;
                buf[i] = 'M';
            }
        }
    }

    printf("%s", buf);
    return 0;
}