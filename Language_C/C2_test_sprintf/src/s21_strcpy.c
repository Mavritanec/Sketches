#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
    char *d = dest;
    const char *s = src;
    while ((*d++ = *s++)) {}
    *d++ = '\0';
    return dest;
}
