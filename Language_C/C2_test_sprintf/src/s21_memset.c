#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
    char *p = (char *)str;
    for (s21_size_t i = 0; i < n; i++) *(p + i) = c;
    return str;
}

/*
void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *p = str;
    for (s21_size_t i = 0; i < n; ++i) {
        *(p + i) = (unsigned char)c;
    }
    return p;
}
*/
