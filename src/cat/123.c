#include <stdio.h>
#include <string.h>

int main() {
    char buf[1000] = "БАЗАР";
    for (int i = 0; i < (int)strlen(buf); i++) {
        unsigned char v = buf[i];
        if (v > 127) {
            if ((v & 127) < 32) {
                for (int j = (int)strlen(buf) + 3; j > i + 3; j--) {
                    buf[j] = buf[j - 3];
                }
                buf[i + 3] = (v & 127) + 64;
                buf[i + 2] = '^';
                buf[i + 1] = '-';
                buf[i] = 'M';
            } else {
                for (int j = (int)strlen(buf) + 2; j > i + 2; j--) {
                    buf[j] = buf[j - 2];
                }
                buf[i + 2] = v & 127;
                buf[i + 1] = '-';
                buf[i] = 'M';
            }
        }
    }
    printf("%s", buf);
    return 0;
}