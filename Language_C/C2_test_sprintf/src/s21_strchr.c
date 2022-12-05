#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
    char *s = S21_NULL;
    s21_size_t i = 0;
    do {
        if (*(str + i) == c) {
            s = (char *)str + i;
            break;
        }
        i++;
    } while (*(str + i - 1) != '\0');
    return s;
}

/*
char *s21_strchr(const char *str, int c) {
    while (*str != (char)c) {
        if (*str == '\0') {
            str = S21_NULL;
            break;
        }
        str++;
    }
    return (char *)str;
}

char *s21_strchr(const char *str, int c) {
    char *s = S21_NULL;

    for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
        if (str[i] == c) {
            s = ((char *)str) + i;
            break;
        }
    }

    return s;
}
*/
