#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 64

int main() {
    setlocale(LC_ALL, "");

    char tmp[BUFF_SIZE];
    char ch[BUFF_SIZE / 16];
    wchar_t w_str[] = L"森b我e爱菠萝";

    int w_str_len = wcstombs(tmp, w_str, BUFF_SIZE);

    printf("%d\n", w_str_len);

    int i = 0, sum = 0;

    while (*(w_str + i)) {
        int w_ch_len = wctomb(ch, w_str[i]);
        sum += w_ch_len;
        printf("%d %d\n", w_ch_len, sum);
        i++;
    }

    return 0;
}
