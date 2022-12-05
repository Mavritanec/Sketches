#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *d = (char *)dest;
    char *s = (char *)src;

    char *tmp = (char *)malloc(n * sizeof(char));
    if (tmp) {
        s21_memcpy(tmp, s, n);
        s21_memcpy(d, tmp, n);
    }
    free(tmp);
    return dest;
}
