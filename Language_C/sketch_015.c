#include <stdio.h>

void s21_strcpy(const char *from_str, char *to_str);

int main() {
    char str_test_1[8] = "qubrick";
    // на забывать про память!
    char str_test_2[8] = {};

    printf("%s\n", str_test_1);

    s21_strcpy(str_test_1, str_test_2);
  
    printf("\n%s %s\n", str_test_1, str_test_2);
    return 0;
}

void s21_strcpy(const char *from_str, char *to_str) {
    const char *src = from_str;
    int i = 0;
    for (; src[i] != '\0'; i++) {
        printf("%c ", from_str[i]);
        to_str[i] = src[i];
        printf("%c ", from_str[i]);
    }
    to_str[i] = '\0';
}
