#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdlib.h>

#define s21_size_t unsigned long int
#define S21_NULL (void *)0
#define BUFF_SIZE 256

void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
s21_size_t s21_strlen(const char *str);

#endif  // SRC_S21_STRING_H_
