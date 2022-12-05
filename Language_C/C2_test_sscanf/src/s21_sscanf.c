#include "s21_string.h"
#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
    va_list(input_args);
    va_start(input_args, format);
    int res = io_sscanf(str, format, input_args);
    va_end(input_args);
    return res;
}

int io_sscanf(const char *input_str, const char *format_str, va_list args) {
    struct lconv *lcnv_ptr = localeconv();
    settings sys_flags = {0, s21_strlen(input_str), *(lcnv_ptr->decimal_point), 0, 0, 0};
    while (*format_str) {
        if (*format_str == '%') {
            parsing flags = {0, 0, 0, 0};
            format_str++;
            if (*format_str == '*') {
                flags.asterisk = 1;
                format_str++;
            }
            check_width(&format_str, &flags);
            check_length(&format_str, &flags);
            check_specifier(&format_str, &flags);
            start_process(input_str, flags, &sys_flags, args);
            if (sys_flags.error) break;
        } else if (check_spaces(*format_str)) {
            while (*(input_str + sys_flags.idx_input_str) == ' ') sys_flags.idx_input_str++;
            format_str++;
        } else {
            if (*format_str == *(input_str + sys_flags.idx_input_str)) {
                sys_flags.idx_input_str++;
                format_str++;
            } else {
                sys_flags.error = 1;
                break;
            }
        }
    }

    if ((!sys_flags.success_res && sys_flags.end_of_input_str) || !sys_flags.len_input_str) sys_flags.success_res = -1;
    return sys_flags.success_res;
}

void check_width(const char **format_str, parsing *flags) {
    if (check_digit(**format_str)) {
        int num;
        for (num = 0; check_digit(**format_str); ++*format_str) num = num * 10 + **format_str - 48;
        flags->width = num;
    }
}

void check_length(const char **format_str, parsing *flags) {
    int code[] = {104, 108, 76};
    for (int i = 0; i < (int) (sizeof(code) / 4); i++) if (**format_str == *(code + i)) {
        flags->length = *(code + i);
        ++*format_str;
        break;
    }
}

void check_specifier(const char **format_str, parsing *flags) {
    int code[] = {99, 100, 101, 69, 102, 103, 71, 105, 110, 111, 112, 115, 117, 120, 88, 37};
    for (int i = 0; i < (int) (sizeof(code) / 4); i++) if (**format_str == *(code + i)) {
        flags->spec = *(code + i);
        ++*format_str;
        break;
    }
}

int check_digit(const char ch) {
    int res = 0;
    if (ch >= '0' && ch <= '9') res = 1;
    return res;
}

void start_process(const char *str, parsing flags, settings *sys_flags, va_list args) {
    switch (flags.spec) {
        case 'c':
            parse_char(str, flags, sys_flags, args);
            break;
        case 'd':
            parse_decimal(str, flags, sys_flags, args);
            break;
        case 'e':
            parse_float(str, flags, sys_flags, args);
            break;
        case 'E':
            parse_float(str, flags, sys_flags, args);
            break;
        case 'f':
            parse_float(str, flags, sys_flags, args);
            break;
        case 'g':
            parse_float(str, flags, sys_flags, args);
            break;
        case 'G':
            parse_float(str, flags, sys_flags, args);
            break;
        case 'i':
            parse_digit(str, flags, sys_flags, args);
            break;
        case 'n':
            parse_counter(flags, sys_flags, args);
            break;
        case 'o':
            parse_octal(str, flags, sys_flags, args);
            break;
        case 'p':
            parse_pointer(str, flags, sys_flags, args);
            break;
        case 's':
            parse_string(str, flags, sys_flags, args);
            break;
        case 'u':
            parse_unsign(str, flags, sys_flags, args);
            break;
        case 'x':
            parse_hex(str, flags, sys_flags, args);
            break;
        case 'X':
            parse_hex(str, flags, sys_flags, args);
            break;
        case '%':
            break;
    }
}

void parse_char(const char *str, parsing flags, settings *sys_flags, va_list args) {
    if (!flags.asterisk) {
        char tmp[BUFF_SIZE / 8] = {'\0'};
        if (flags.length == 'l') {
            // !!!доделать!!!
            wchar_t *w_ch = va_arg(args, wchar_t *);
            size_t wch_len = wcstombs(tmp, w_ch, BUFF_SIZE / 8);
            *w_ch = *(str + sys_flags->idx_input_str);
            sys_flags->success_res += wch_len;
        } else {
            char *ch = va_arg(args, char *);
            *ch = *(str + sys_flags->idx_input_str);
            if (*(str + sys_flags->idx_input_str) == '\0') {
                sys_flags->end_of_input_str = 1;
            } else {
                sys_flags->success_res++;
            }
        }
    }
    if (flags.width > 1) {
        if (sys_flags->idx_input_str + flags.width < sys_flags->len_input_str) {
            sys_flags->idx_input_str += flags.width;
        } else {
            sys_flags->idx_input_str = sys_flags->len_input_str;
            sys_flags->error = 1;
        }
    } else {
        sys_flags->idx_input_str++;
        if (!*(str + sys_flags->idx_input_str)) sys_flags->error = 1;
    }
}

void parse_decimal(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    long int num = 0;
    int change = 0;
    while (check_digit(*(str + sys_flags->idx_input_str))) {
        if (flags.width == sys_flags->idx_input_str - jdx) break;
        num = (num * 10) + *(str + sys_flags->idx_input_str) - 48;
        change++;
        sys_flags->idx_input_str++;
    }
    if (*(str + sys_flags->idx_input_str) == '\0') sys_flags->end_of_input_str = 1;
    if (change) {
        if (!flags.asterisk) {
            switch (flags.length) {
                case 104: {
                    short int *res = va_arg(args, short int *);
                    *res = num * sign;
                    break;
                }
                case 108: {
                    long int *res = va_arg(args, long int *);
                    *res = num * sign;
                    break;
                }
                default: {
                    int *res = va_arg(args, int *);
                    *res = num * sign;
                    break;
                }
            }
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

void parse_float(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    // infinity and nan

    long double num = 0;
    int position_e = 0, counter_num = 0, counter_power_e = 0, power = -1;
    int p = 0, e = 0, plus = 1, power_e = 0;
    while (check_digit(*(str + sys_flags->idx_input_str)) ||
                       *(str + sys_flags->idx_input_str) == 'e' ||
                       *(str + sys_flags->idx_input_str) == 'E' ||
                       *(str + sys_flags->idx_input_str) == '+' ||
                       *(str + sys_flags->idx_input_str) == '-' ||
                       *(str + sys_flags->idx_input_str) == sys_flags->dec_point) {
        if (flags.width == sys_flags->idx_input_str - jdx) break;
        if (*(str + sys_flags->idx_input_str) == sys_flags->dec_point && p) break;
        if ((*(str + sys_flags->idx_input_str) == 'e' || *(str + sys_flags->idx_input_str) == 'E') && e) break;
        if (*(str + sys_flags->idx_input_str) == sys_flags->dec_point) p = 1;
        if (*(str + sys_flags->idx_input_str) == 'e' || *(str + sys_flags->idx_input_str) == 'E') {
            e = 1;
            p = 1;
            position_e = sys_flags->idx_input_str;
        }
        if ((*(str + sys_flags->idx_input_str) == '+' || *(str + sys_flags->idx_input_str) == '-') &&
            (*(str + sys_flags->idx_input_str - 1) != 'e' && *(str + sys_flags->idx_input_str) != 'E')) break;
        if (*(str + sys_flags->idx_input_str) == '+' && e && (*(str + sys_flags->idx_input_str - 1) == 'e' ||
            *(str + sys_flags->idx_input_str - 1) == 'E')) plus = 1;
        if (*(str + sys_flags->idx_input_str) == '-' && e && (*(str + sys_flags->idx_input_str - 1) == 'e' ||
            *(str + sys_flags->idx_input_str - 1) == 'E')) plus = -1;
        if (check_digit(*(str + sys_flags->idx_input_str)) && !p) {
            num = (num * 10) + (*(str + sys_flags->idx_input_str) - 48);
            counter_num++;
        }
        if (check_digit(*(str + sys_flags->idx_input_str)) && p && !e) {
            num = num + (*(str + sys_flags->idx_input_str) - 48) * pow(10, power);
            counter_num++;
            power--;
        }
        if (check_digit(*(str + sys_flags->idx_input_str)) && p && e) {
            counter_power_e++;
            power_e = (power_e * 10) + (*(str + sys_flags->idx_input_str) - 48);
        }
        sys_flags->idx_input_str++;
    }
    if (!counter_power_e &&  e) sys_flags->idx_input_str = position_e;
    if (*(str + sys_flags->idx_input_str) == '\0') sys_flags->end_of_input_str = 1;
    if (counter_num) {
        if (!flags.asterisk) {
            switch (flags.length) {
                case 76: {
                    long double *res = va_arg(args, long double *);
                    *res = num * sign * pow(10, power_e * plus);
                    break;
                }
                case 108: {
                    double *res = va_arg(args, double *);
                    *res = num * sign * pow(10, power_e * plus);
                    break;
                }
                default: {
                    float *res = va_arg(args, float *);
                    *res = num * sign * pow(10, power_e * plus);
                    break;
                }
            }
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

void parse_digit(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sys_flags->idx_input_str++;
    }

    int zero = 0, x = 0;
    char tmp[BUFF_SIZE] = {'\0'};
    s21_memmove(tmp, str + sys_flags->idx_input_str, flags.width);
    if (*tmp == 48) zero = 1;
    if ((*(tmp + 1) == 'x' || *(tmp + 1) == 'X') && zero == 1) x = 1;
    sys_flags->idx_input_str = jdx;
    if (zero == 0) parse_decimal(str, flags, sys_flags, args);
    if (zero == 1 && x == 0) parse_octal(str, flags, sys_flags, args);
    if (zero == 1 && x == 1) parse_hex(str, flags, sys_flags, args);
}

void parse_counter(parsing flags, settings *sys_flags, va_list args) {
    if (!flags.asterisk) {
        int *num = va_arg(args, int *);
        *num = sys_flags->idx_input_str;
    }
}

void parse_octal(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    char tmp[BUFF_SIZE] = {'\0'};
    int nozero = 0, change = 0;
    while (*(str + sys_flags->idx_input_str) != ' ' &&
           *(str + sys_flags->idx_input_str) != '\t' &&
           *(str + sys_flags->idx_input_str) != '\n') {
        if (flags.width == sys_flags->idx_input_str - jdx || !check_oct_num(*(str + sys_flags->idx_input_str))) break;
        if (nozero) {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        if (*(str + sys_flags->idx_input_str) != '0' && nozero == 0) {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        change++;
        sys_flags->idx_input_str++;
    }
    *(tmp + nozero) = '\0';

    // или long int, рассмотреть!
    int num = 0;
    int digit, len = (int) s21_strlen(tmp);
    for (jdx = 0; jdx < len; jdx++) {
        digit =  convert_hex(*(tmp + jdx));
        num = num + digit * pow(8, len - jdx - 1);
    }
    if (*(str + sys_flags->idx_input_str) == '\0' && sys_flags->success_res) sys_flags->end_of_input_str = 1;
    if (change) {
        if (!flags.asterisk) {
            int *res = va_arg(args, int *);
            *res = num * sign;
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

void parse_pointer(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    char tmp[BUFF_SIZE] = {'\0'};
    int nozero = 0, zero = 0, x_value = 0, x_position = 0, change = 0;
    while (*(str + sys_flags->idx_input_str) == 'x' ||
           *(str + sys_flags->idx_input_str) == 'X' ||
           check_hex_num(*(str + sys_flags->idx_input_str))) {
        if (flags.width == sys_flags->idx_input_str - jdx) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && x_value == 1) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && nozero != 0 && x_value == 0) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && nozero == 0 && x_value == 0) {
            if (zero == 1) {
                x_value = 1;
                x_position = sys_flags->idx_input_str;
                zero = 0;
            } else if (zero == 0) {
                sys_flags->error = 1;
                break;
            } else {
                break;
            }
        }
        if (*(str + sys_flags->idx_input_str) == '0' && nozero == 0) zero++;
        if (nozero != 0 && check_hex_num(*(str + sys_flags->idx_input_str)) == 1) {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        if (*(str + sys_flags->idx_input_str) != '0' && check_hex_num(*(str + sys_flags->idx_input_str)) == 1 && nozero == 0) {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        sys_flags->idx_input_str++;
        change++;
    }

    int num = 0;
    int digit, len = (int) s21_strlen(tmp);
    for (jdx = 0; jdx < len; jdx++) {
        digit =  convert_hex(*(tmp + jdx));
        num = num + digit * pow(16, len - jdx - 1);
    }
    if (x_value == 1 && (zero == 0 && nozero == 0)) sys_flags->idx_input_str = x_position;
    if (*(str + sys_flags->idx_input_str) == '\0') sys_flags->end_of_input_str = 1;
    if (change) {
        if (!flags.asterisk) {
            int *res = va_arg(args, int *);
            *res = num * sign;
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

void parse_string(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int jdx = sys_flags->idx_input_str;
    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    while (flags.width != sys_flags->idx_input_str - jdx) {
        if (check_spaces(*(str + sys_flags->idx_input_str))) break;
        if (*(str + sys_flags->idx_input_str) == '\0') {
            sys_flags->error = 1;
            break;
        }
        sys_flags->idx_input_str++;
    }

    char tmp[BUFF_SIZE] = {'\0'};
    s21_memmove(tmp, str + jdx, sys_flags->idx_input_str - jdx);
//    *(tmp + sys_flags->idx_input_str - jdx) = '\0';

    if (!flags.asterisk) {
        char *ch = (char *) va_arg(args, int *);
        *ch = '\0';
        s21_strcat(ch, tmp);
        sys_flags->success_res++;
    }
}

void parse_unsign(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    unsigned int num = 0;
    int change = 0;
    while (check_digit(*(str + sys_flags->idx_input_str))) {
        if (flags.width != 0 && flags.width == sys_flags->idx_input_str - jdx) break;
        num = num * 10 + *(str + sys_flags->idx_input_str) - 48;
        sys_flags->idx_input_str++;
        change++;
    }
    if (*(str + sys_flags->idx_input_str) == '\0') sys_flags->end_of_input_str = 1;
    if (change) {
        if (!flags.asterisk) {
            unsigned int *res = va_arg(args, unsigned int *);
            *res = num * sign;
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

void parse_hex(const char *str, parsing flags, settings *sys_flags, va_list args) {
    while (check_spaces(*(str + sys_flags->idx_input_str))) sys_flags->idx_input_str++;

    int sign = 1;
    int jdx = sys_flags->idx_input_str;
    if (*(str + sys_flags->idx_input_str) == '+') {
        sys_flags->idx_input_str++;
    } else if (*(str + sys_flags->idx_input_str) == '-') {
        sign = -1;
        sys_flags->idx_input_str++;
    }

    if (!flags.width) {
        flags.width = sys_flags->len_input_str - jdx;
    } else if (flags.width >= sys_flags->len_input_str - jdx) {
        flags.width = sys_flags->len_input_str - jdx;
    }

    int change = 0;
    char tmp[BUFF_SIZE] = {'\0'};
    int nozero = 0, zero = 0, x_value = 0, x_position = 0;
    while (*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X' || check_hex_num(*(str + sys_flags->idx_input_str))) {
        if (flags.width == sys_flags->idx_input_str - jdx) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && x_value) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && nozero && !x_value) break;
        if ((*(str + sys_flags->idx_input_str) == 'x' || *(str + sys_flags->idx_input_str) == 'X') && !nozero && !x_value) {
            if (zero == 1) {
                x_value = 1;
                x_position = sys_flags->idx_input_str;
                zero = 0;
            } else if (zero == 0) {
                sys_flags->error = 1;
                break;
            } else {
                break;
            }
        }
        if (nozero == 0 && *(str + sys_flags->idx_input_str) == '0') zero++;
        if (nozero != 0 && check_hex_num(*(str + sys_flags->idx_input_str)) == 1) {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        if (nozero == 0 && check_hex_num(*(str + sys_flags->idx_input_str)) == 1 && *(str + sys_flags->idx_input_str) != '0') {
            *(tmp + nozero) = *(str + sys_flags->idx_input_str);
            nozero++;
        }
        change++;
        sys_flags->idx_input_str++;
    }
    int len = s21_strlen(tmp);
    unsigned int digit, num = 0;
    for (jdx = 0; jdx < len; jdx++) {
        digit = convert_hex(*(tmp + jdx));
        num = num + digit * pow(16, len - 1 - jdx);
    }
    if (x_value == 1 && (zero == 0 && nozero == 0)) sys_flags->idx_input_str = x_position;
    if (*(str + sys_flags->idx_input_str) == '\0') sys_flags->end_of_input_str = 1;
    if (change) {
        if (!flags.asterisk) {
            switch (flags.length) {
                case 104: {
                    unsigned short int *res = va_arg(args, unsigned short int *);
                    *res = num * sign;
                    break;
                }
                case 108: {
                    unsigned long int *res = va_arg(args, unsigned long int *);
                    *res = num * sign;
                    break;
                }
                default: {
                    unsigned int *res = va_arg(args, unsigned int *);
                    *res = num * sign;
                    break;
                }
            }
            sys_flags->success_res++;
        }
    } else {
        sys_flags->error = 1;
    }
}

int check_spaces(char ch) {
    int res = 0;
    if (ch == ' ' || ch == '\t' || ch == '\n') res = 1;
    return res;
}

int check_oct_num(char ch) {
    int res = 0;
    if (ch >= '0' && ch <= '7') res = 1;
    return res;
}

int check_hex_num(char ch) {
    int res = 0;
    if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) res = 1;
    return res;
}

int convert_hex(char value) {
    int ch;
    if (value >= '0' && value <= '9') {
        ch = (int) value - 48;
    } else if (value >= 'a' && value <= 'f') {
        ch = (int) value - 87;
    } else if (value >= 'A' && value <= 'F') {
        ch = (int) value - 55;
    } else {
        ch = 0;
    }
    return ch;
}
