#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 64

int main() {
    setlocale(LC_ALL, "");

    char buff[BUFF_SIZE] = {'\0'};
    int prec = 7;
    int width = 3;
    int minus = 0;

    wchar_t w_str[] = L"森b我e爱菠萝";
    char tmp[BUFF_SIZE] = {'\0'};
    int w_str_len = 0;

    if (prec) {
        int i_w_ch = 0;
        while (prec > 0 && *(w_str + i_w_ch)) {
            char w_ch[5] = {'\0'};
            int w_ch_len = wctomb(w_ch, *(w_str + i_w_ch));
            prec -= w_ch_len;
            if (prec >= 0) {
            printf("ch: %d str: %lc str: %s\n", w_ch_len, *(w_str + i_w_ch), w_ch);
            strcat(tmp, w_ch);
            i_w_ch++;
            w_str_len += w_ch_len;
            }
        }
    } else {
        w_str_len = wcstombs(tmp, w_str, 64);
    }
    printf("str_len: %d\n", w_str_len);
    int shift = width - w_str_len;
    if (minus && shift > 0) {
        strcpy(buff, tmp);
        memset(buff + w_str_len, ' ', shift);
    } else if (shift > 0) {
        memset(buff, ' ', shift);
        strcpy(buff + shift, tmp);
    } else {
        strcpy(buff, tmp);
    }

    printf("|%s|%ls|%s|\n", buff, w_str, tmp);

    return 0;
}
