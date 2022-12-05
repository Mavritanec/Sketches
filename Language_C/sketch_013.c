#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main() {
    wchar_t ch = 'G';
    wchar_t str[5];
    char res[10];

    str[0] = ch;

    int i = 0;
    while (str[i] != '\0') {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';

    printf("%d\n", i);
    printf("%c\n", str[0]);
    printf("%s\n", res);
    printf("%c\n", res[0]);
    return 0;
}
