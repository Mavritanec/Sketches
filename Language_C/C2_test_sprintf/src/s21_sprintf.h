#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <locale.h>
#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>
#include <math.h>

#define s21_size_t unsigned long int
#define BUFF_SIZE 256

typedef struct {
    int minus;
    int plus;
    int neg_num;
    int space;
    int zero;
    int sharp;
    int width;
    int prec;
    int check_prec;
    char length;
    char spec;
    char dec_point;
} spec;

int s21_sprintf(char *str, const char *format, ...);
int io_sprintf(char *output_str, const char *input_str, va_list args);

void parse_flags(const char **input_str, spec *flag);
void parse_width(const char **input_str, spec *flag, va_list args);
void parse_precision(const char **input_str, spec *flag, va_list args);
void parse_length(const char **input_str, spec *flag);
void parse_specifier(const char **input_str, spec *flag);

int collect_digits(const char **sbl);

void main_process(char *buff, spec flag, va_list args);

void int_to_string(spec flag, char *buff, va_list args);
void unsign_to_string(spec flag, char *buff, va_list args);
void octal_to_string(spec flag, char *buff, va_list args);
void hex_to_string(spec flag, char *buff, va_list args);
void char_to_string(spec flag, char *buff, va_list args);
void str_to_string(spec flag, char *buff, va_list args);
void ptr_to_string(spec flag, char *buff, va_list args);
void float_to_string(spec flag, char *buff, va_list args);
void mantiss_to_string(spec flag, char *buff, va_list args);
void float_g_to_string(spec flag, char *buff, va_list args);

void to_upper(char *str);

void int_num_to_string(spec *flag, char *buff, int64_t val, int base);
void unsigned_num_to_string(char *buff, uint64_t val, int base);
void double_num_to_string(spec *flag, char *buff, long double val);

void format_prec(spec flag, char *buff);
void format_flags(spec flag, char *buff);
void format_char(spec flag, char *buff, char ch);
void format_wide_char(spec flag, char *buff, wchar_t w_ch);
void format_string(spec flag, char *buff, char *str);
void format_wide_string(spec flag, char *buff, wchar_t *w_str);
void format_g_prec(spec flag, char *buff, int prec);

int check_int_spec(char ch);
void prepend_ox(spec flag, char *buff);
int is_all_zeroes(char *buff);
void prepend_mantiss(char *str, int pow, char sign);
void remove_trailing_zeroes(spec flag, char *buff);

#endif  // SRC_S21_SPRINTF_H_
