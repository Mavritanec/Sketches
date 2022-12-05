#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#include <stdarg.h>
#include <math.h>
#include <locale.h>

typedef struct {
    int idx_input_str;
    int len_input_str;
    int dec_point;
    int success_res;
    int error;
    int end_of_input_str;
} settings;

typedef struct {
    int asterisk;
    int width;
    int length;
    int spec;
} parsing;

int s21_sscanf(const char *str, const char *format, ...);
int io_sscanf(const char *input_str, const char *format_str, va_list args);

void check_width(const char **format_str, parsing *flags);
void check_length(const char **format_str, parsing *flags);
void check_specifier(const char **format_str, parsing *flags);

int check_digit(const char ch);

void start_process(const char *str, parsing flags, settings *sys_flags, va_list args);

void parse_char(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_decimal(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_float(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_digit(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_counter(parsing flags, settings *sys_flags, va_list args);
void parse_octal(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_pointer(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_string(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_unsign(const char *str, parsing flags, settings *sys_flags, va_list args);
void parse_hex(const char *str, parsing flags, settings *sys_flags, va_list args);

int check_spaces(char ch);
int check_oct_num(char ch);
int check_hex_num(char ch);
int convert_hex(char value);

#endif  // SRC_S21_SSCANF_H_
