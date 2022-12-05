#include "s21_string.h"
#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
    va_list(input_args);
    va_start(input_args, format);
    int res = io_sprintf(str, format, input_args);
    va_end(input_args);
    return res;
}

// посмотреть мою реализацию и поправить по отношению к ней
// имеется ввиду char *start_ch и действия с этой переменной
int io_sprintf(char *output_str, const char *input_str, va_list args) {
    char *start_ch = output_str;
    struct lconv *lcnv_ptr = localeconv();
    char dec_point = *(lcnv_ptr->decimal_point);
    while (*input_str) {
        if (*input_str != '%') {
            *output_str++ = *input_str++;
            continue;
        }
        spec flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, '0', '0', dec_point};
        parse_flags(&input_str, &flag);
        parse_width(&input_str, &flag, args);
        parse_precision(&input_str, &flag, args);
        parse_length(&input_str, &flag);
        parse_specifier(&input_str, &flag);
        char buff[BUFF_SIZE] = {'\0'};
        main_process(buff, flag, args);
        for (int i = 0; *(buff + i); i++, output_str++) *output_str = *(buff + i);
        // обработать (засунуть) в main_process
        if (flag.spec == 'n') {
            int *ret = va_arg(args, int *);
            *ret = output_str - start_ch;
        }
    }
    *output_str = '\0';
    return output_str - start_ch;
}

void parse_flags(const char **input_str, spec *flag) {
    int check = 1;
    while (check) {
        ++*input_str;
        switch (**input_str) {
            case '-': flag->minus = 1; break;
            case '+': flag->plus = 1; break;
            case ' ': flag->space = 1; break;
            case '#': flag->sharp = 1; break;
            case '0': flag->zero = 1; break;
            default: check = 0; break;
        }
    }
}

void parse_width(const char **input_str, spec *flag, va_list args) {
    if ('0' <= **input_str && **input_str <= '9') {
        flag->width = collect_digits(input_str);
    } else if (**input_str == '*') {
        flag->width = va_arg(args, int);
        ++*input_str;
    }
}

void parse_precision(const char **input_str, spec *flag, va_list args) {
    if (**input_str == '.') {
        flag->check_prec = 1;
        ++*input_str;
        if ('0' <= **input_str && **input_str <= '9') {
            flag->prec = collect_digits(input_str);
        } else if (**input_str == '*') {
            flag->prec = va_arg(args, int);
            if (flag->prec < 0) flag->check_prec = 0;
            ++*input_str;
        }
    }
}

int collect_digits(const char **sbl) {
    int num, ch;
    for (num = 0; '0' <= (ch = **sbl) && ch <= '9'; ++*sbl) num = num * 10 + ch - '0';
    return num;
}

void parse_length(const char **input_str, spec *flag) {
    switch (**input_str) {
        case 'h': flag->length = 'h'; ++*input_str; break;
        case 'l': flag->length = 'l'; ++*input_str; break;
        case 'L': flag->length = 'L'; ++*input_str; break;
    }
}

void parse_specifier(const char **input_str, spec *flag) {
    switch (**input_str) {
        case 'c': flag->spec = 'c'; ++*input_str; break;
        case 'd': flag->spec = 'd'; ++*input_str; break;
        case 'e': flag->spec = 'e'; ++*input_str; break;
        case 'E': flag->spec = 'E'; ++*input_str; break;
        case 'f': flag->spec = 'f'; ++*input_str; break;
        case 'g': flag->spec = 'g'; ++*input_str; break;
        case 'G': flag->spec = 'G'; ++*input_str; break;
        case 'i': flag->spec = 'i'; ++*input_str; break;
        case 'n': flag->spec = 'n'; ++*input_str; break;
        case 'o': flag->spec = 'o'; ++*input_str; break;
        case 'p': flag->spec = 'p'; ++*input_str; break;
        case 's': flag->spec = 's'; ++*input_str; break;
        case 'u': flag->spec = 'u'; ++*input_str; break;
        case 'x': flag->spec = 'x'; ++*input_str; break;
        case 'X': flag->spec = 'X'; ++*input_str; break;
        case '%': flag->spec = '%'; ++*input_str; break;
    }
}

void main_process(char *buff, spec flag, va_list args) {
    // отработка отрицательной ширины переданной через аргумент
    if (flag.width < 0) {
        flag.width = -flag.width;
        if (!flag.minus) flag.minus = 1;
    }
    switch (flag.spec) {
        case 'c':
            char_to_string(flag, buff, args);
            break;
        case 'd':
        case 'i':
            int_to_string(flag, buff, args);
            break;
        case 'e':
        case 'E':
            mantiss_to_string(flag, buff, args);
            break;
        case 'f':
            float_to_string(flag, buff, args);
            break;
        case 'g':
        case 'G':
            float_g_to_string(flag, buff, args);
            break;
        // реализовать тут
//        case 'n':
//            break;
        case 'o':
            octal_to_string(flag, buff, args);
            break;
        case 'p':
            ptr_to_string(flag, buff, args);
            break;
        case 's':
            str_to_string(flag, buff, args);
            break;
        case 'u':
            unsign_to_string(flag, buff, args);
            break;
        case 'x':
        case 'X':
            hex_to_string(flag, buff, args);
            break;
        case '%':
            *buff = '%';
            break;
    }
    if (flag.spec == 'G' || flag.spec == 'E' || flag.spec == 'X') to_upper(buff);
}

void to_upper(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
        str++;
    }
}

void int_to_string(spec flag, char *buff, va_list args) {
    int64_t val = va_arg(args, int64_t);
    switch (flag.length) {
        case 'h': val = (int16_t) val; break;
        case '0': val = (int32_t) val; break;
    }
    int_num_to_string(&flag, buff, val, 10);
    format_prec(flag, buff);
    format_flags(flag, buff);
}

void unsign_to_string(spec flag, char *buff, va_list args) {
    uint64_t val = va_arg(args, uint64_t);
    switch (flag.length) {
        case 'h': val = (uint16_t) val; break;
        case '0': val = (uint32_t) val; break;
        // зачем, он и так 64-й по умолчанию
        case 'l': val = (uint64_t) val; break;
    }
    unsigned_num_to_string(buff, val, 10);
    format_prec(flag, buff);
    format_flags(flag, buff);
}

void octal_to_string(spec flag, char *buff, va_list args) {
    *buff = '0';
    int_num_to_string(&flag, buff + flag.sharp, va_arg(args, int64_t), 8);
    format_prec(flag, buff);
    format_flags(flag, buff);
}

void hex_to_string(spec flag, char *buff, va_list args) {
    uint64_t val = va_arg(args, uint64_t);
    // часто повторяется, подумать, как упростить (создать функцию)
    switch (flag.length) {
        case 'h': val = (uint16_t) val; break;
        case '0': val = (uint32_t) val; break;
        case 'l': val = (uint64_t) val; break;
    }
    unsigned_num_to_string(buff, val, 16);
    format_prec(flag, buff);
    if (flag.sharp) prepend_ox(flag, buff);
    format_flags(flag, buff);
}

void char_to_string(spec flag, char *buff, va_list args) {
    if (flag.length == 'l') {
        wchar_t w_ch;
        w_ch = va_arg(args, wchar_t);
        format_wide_char(flag, buff, w_ch);
    } else {
        char ch;
        ch = va_arg(args, int);
        format_char(flag, buff, ch);
    }
}

void str_to_string(spec flag, char *buff, va_list args) {
    if (flag.length == 'l') {
        wchar_t *w_str = va_arg(args, wchar_t *);
        format_wide_string(flag, buff, w_str);
    } else {
        char *str = va_arg(args, char *);
        format_string(flag, buff, str);
    }
}

void ptr_to_string(spec flag, char *buff, va_list args) {
    unsigned_num_to_string(buff, va_arg(args, uint64_t), 16);
    format_prec(flag, buff);
    prepend_ox(flag, buff);
    format_flags(flag, buff);
}

void float_to_string(spec flag, char *buff, va_list args) {
    long double val = 0;
    if (flag.length == 'L') {
        val = va_arg(args, long double);
    } else {
        val = va_arg(args, double);
    }
    if (!flag.check_prec) flag.prec = 6;
    double_num_to_string(&flag, buff, val);
    format_flags(flag, buff);
}

void mantiss_to_string(spec flag, char *buff, va_list args) {
    long double val = 0;
    if (flag.length == 'L') {
        val = va_arg(args, long double);
    } else {
        val = va_arg(args, double);
    }
    int pow = 0;
    char sign = '-';
    if ((int) val) sign = '+';
    if ((int) val - val) {
        while ((int) val == 0) {
            pow++;
            val *= 10;
        }
    } else {
        sign = '+';
    }
    while ((int) val / 10 != 0) {
        pow++;
        val /= 10;
    }
    if (!flag.check_prec) flag.prec = 6;
    double_num_to_string(&flag, buff, val);
    prepend_mantiss(buff, pow, sign);
    format_flags(flag, buff);
}

void float_g_to_string(spec flag, char *buff, va_list args) {
    long double num = 0;
    if (flag.length == 'L') {
        num = va_arg(args, long double);
    } else {
        num = va_arg(args, double);
    }

    if (!flag.check_prec) flag.prec = 6;
    if (!flag.prec) flag.prec = 1;

    long double int_num = num;
    int int_num_len = 0;
    while ((int) int_num > 10) {
        int_num_len++;
        int_num /= 10;
    }

    long double fract_num = num;
    int fract_num_zero = 0;
    if (!int_num_len) {
        if ((int) num - num) {
            while (!((int) fract_num)) {
                fract_num_zero++;
                fract_num *= 10;
            }
            fract_num = roundl(fract_num * 10e+12) / 10e+12;
        }
    }

    if (int_num_len > flag.prec) {
        double_num_to_string(&flag, buff, int_num);
    } else if (fract_num_zero > 4) {
        double_num_to_string(&flag, buff, fract_num);
    } else {
        if (flag.check_prec) flag.prec += fract_num_zero;
        double_num_to_string(&flag, buff, num);
    }
    format_g_prec(flag, buff, flag.prec);
    if (!flag.sharp) remove_trailing_zeroes(flag, buff);
    if (int_num_len > flag.prec && flag.check_prec) {
        prepend_mantiss(buff, int_num_len, '+');
    } else if (fract_num_zero > 4) {
        prepend_mantiss(buff, fract_num_zero, '-');
    }
    format_flags(flag, buff);
}

void int_num_to_string(spec *flag, char *buff, int64_t val, int base) {
    char tmp[BUFF_SIZE] = {'\0'};
    int i = BUFF_SIZE - 2;
    if (val < 0) {
        flag->neg_num = 1;
        val = -val;
    }
    if (!val) *(tmp + i) = '0';
    while (val > 0) {
        // расшифровать эту запись
        *(tmp + --i) = "0123456789abcdef"[val % base];
        val /= base;
    }
    for (int j = 0; *(tmp + i); i++, j++) *(buff +j) = *(tmp +i);
}

void unsigned_num_to_string(char *buff, uint64_t val, int base) {
    char tmp[BUFF_SIZE + 1] = {'\0'};
    int i = BUFF_SIZE - 1;
    if (!val) *(tmp + i--) = '0';
    for (; val && i; --i, val /= base) *(tmp + i) = "0123456789abcdef"[val % base];
    for (int j = 0; *(tmp + i + 1); i++, j++) *(buff + j) = *(tmp + i + 1);
}

void double_num_to_string(spec *flag, char *buff, long double val) {
    char tmp[BUFF_SIZE] = {'\0'};
    int i = BUFF_SIZE - 2;
    if (val < 0) {
        flag->neg_num = 1;
        val = -val;
    }
    long double l = 0, r = modfl(val, &l);
    if (!flag->prec) {
        l = roundl(val);
        r = 0;
    }
    char fractions[BUFF_SIZE] = {'\0'};
    for (int j = 0; j < flag->prec; j++) {
        r *= 10;
        *(fractions + j) = (int) r + '0';
    }
    long long right = roundl(r), left = l;
    if (!right) {
        for (int j = 0; j < flag->prec; i--, j++) *(tmp + i) = '0';
    } else {
        for (int j = s21_strlen(fractions); right || j > 0;
            right /= 10, i--, j--)
            *(tmp + i) = (int) (right % 10 + 0.001) + '0';
    }
    if ((flag->check_prec && flag->prec != 0) || (int) r ||
        (!flag->check_prec && !val) || s21_strlen(fractions) ||
        (flag->sharp && (flag->spec == 'e' ||
                         flag->spec == 'E' ||
                         flag->spec == 'f'))) *(tmp + i--) = flag->dec_point;
    if (!left) {
        *(tmp + i--) = '0';
    } else {
        for (; left; left /= 10, i--) *(tmp + i) = (int) (left % 10) + '0';
    }
    for (int j = 0; *(tmp + i + 1); i++, j++) *(buff + j) = *(tmp + i + 1);
}

void format_prec(spec flag, char *buff) {
    char tmp[BUFF_SIZE] = {'\0'};
    int sign = 0;
    int len = s21_strlen(buff);
    if (*buff == '-') {
        *tmp = '-';
        len--;
        sign = 1;
    }
    if (flag.prec > len) {
        int i;
        for (i = sign; i < flag.prec - len + sign; i++) *(tmp + i) = '0';
        for (int j = sign; *(buff +j); j++, i++) *(tmp +i) = *(buff + j);
        s21_strcpy(buff, tmp);
    }
    if (flag.check_prec && flag.prec == 0 && check_int_spec(flag.spec) && *buff == '0')
        *buff = '\0';
}

void format_flags(spec flag, char *buff) {
    char tmp[BUFF_SIZE + 1] = {'\0'};
    int len = s21_strlen(buff);
    int add_shift = -1;
    if (flag.minus) {
        if (flag.neg_num && flag.spec != 'u') {
            *tmp = '-';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.plus && flag.spec != 'u') {
            *tmp = '+';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.space && flag.spec != 'u') {
            *tmp = ' ';
            s21_strcpy(tmp + 1, buff);
        } else {
            add_shift = 0;
            s21_strcpy(tmp, buff);
        }
        s21_strcpy(buff, tmp);
        if (flag.width > len) {
            int len_fill = flag.width - len + add_shift;
            s21_strcpy(tmp, buff);
            s21_memset(tmp + s21_strlen(tmp), ' ', len_fill);
            s21_strcpy(buff, tmp);
        }
    } else if (flag.zero) {
        if (!(flag.neg_num || flag.plus || flag.space)) add_shift = 0;
        if (flag.width > len) {
            int len_fill = flag.width - len + add_shift;
            s21_memset(tmp, '0', len_fill);
            s21_strcpy(tmp + len_fill, buff);
            s21_strcpy(buff, tmp);
        }
        if (flag.neg_num && flag.spec != 'u') {
            *tmp = '-';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.plus && flag.spec != 'u') {
            *tmp = '+';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.space && flag.spec != 'u') {
            *tmp = ' ';
            s21_strcpy(tmp + 1, buff);
        } else {
            s21_strcpy(tmp, buff);
        }
        s21_strcpy(buff, tmp);
    } else {
        if (flag.neg_num && flag.spec != 'u') {
            *tmp = '-';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.plus && flag.spec != 'u') {
            *tmp = '+';
            s21_strcpy(tmp + 1, buff);
        } else if (flag.space && flag.spec != 'u') {
            *tmp = ' ';
            s21_strcpy(tmp + 1, buff);
        } else {
            add_shift = 0;
            s21_strcpy(tmp, buff);
        }
        s21_strcpy(buff, tmp);
        if (flag.width > len) {
            int len_fill = flag.width - len + add_shift;
            s21_memset(tmp, ' ', len_fill);
            s21_strcpy(tmp + len_fill, buff);
            s21_strcpy(buff, tmp);
        }
    }
}

void format_char(spec flag, char *buff, char ch) {
    if (!flag.minus && flag.width) {
        for (int i = 0; i < flag.width - 1; i++) *(buff + i) = ' ';
        *(buff + flag.width - 1) = ch;
    } else if (flag.width) {
        *buff = ch;
        for (int i = 1; i < flag.width; i++) *(buff + i) = ' ';
    } else {
        *buff = ch;
    }
}

void format_wide_char(spec flag, char *buff, wchar_t w_ch) {
    if (!flag.minus && flag.width) {
        for (int i = 0; i < flag.width - 1; i++) *(buff + i) = ' ';
        wctomb(buff, w_ch);
    } else if (flag.width) {
        wctomb(buff, w_ch);
        for (int i = s21_strlen(buff); i < flag.width; i++) *(buff + i) = ' ';
    } else {
        wctomb(buff, w_ch);
    }
}

void format_string(spec flag, char *buff, char *str) {
    char tmp[BUFF_SIZE] = {'\0'};
    s21_strcpy(tmp, str);
//    if (flag.prec < 0) flag.check_prec = 0;
    if (flag.check_prec) *(tmp + flag.prec) = '\0';
    int len = s21_strlen(tmp);
    int shift = flag.width - len;

    if (flag.minus && shift > 0) {
        s21_strcpy(buff, tmp);
        s21_memset(buff + len, ' ', shift);
    } else if (shift > 0) {
        s21_memset(buff, ' ', shift);
        s21_strcpy(buff + shift, tmp);
    } else {
        s21_strcpy(buff, tmp);
    }
}

void format_wide_string(spec flag, char *buff, wchar_t *w_str) {
    char tmp[BUFF_SIZE] = {'\0'};
    int w_str_len = 0;
    if (flag.prec) {
        int i_w_ch = 0;
        while (flag.prec > 0 && *(w_str + i_w_ch)) {
            char w_ch[5] = {'\0'};
            int w_ch_len = wctomb(w_ch, *(w_str + i_w_ch));
            flag.prec -= w_ch_len;
            if (flag.prec >= 0) {
                s21_strcat(tmp, w_ch);
                i_w_ch++;
                w_str_len += w_ch_len;
            }
        }
    } else {
        w_str_len = wcstombs(tmp, w_str, BUFF_SIZE / 2);
    }
    int shift = flag.width - w_str_len;
    if (flag.minus && shift > 0) {
        s21_strcpy(buff, tmp);
        s21_memset(buff + w_str_len, ' ', shift);
    } else if (shift > 0) {
        s21_memset(buff, ' ', shift);
        s21_strcpy(buff + shift, tmp);
    } else {
        s21_strcpy(buff, tmp);
    }
}

void format_g_prec(spec flag, char *buff, int prec) {
    int i_digs = 1;
    int i_len = 0;
    int check_dec_point = 0;
    for (; *(buff + i_len) != '\0'; i_len++) {
        if (*(buff + i_len) == flag.dec_point) {
            check_dec_point = 1;
            continue;
        }
        if (i_digs == prec && *(buff + i_len + 1) != '\0') {
            int next_dig = 1;
            if (*(buff + i_len + next_dig) == flag.dec_point) next_dig = 2;  // может попасть на конец строки
            if (*(buff + i_len + next_dig) - '0' >= 5) *(buff + i_len) = (char) (*(buff + i_len) + 1);
            *(buff + i_len + next_dig) = '\0';
            break;
        }
        i_digs++;
    }
    if (!check_dec_point && flag.sharp) *(buff + i_len + 1) = flag.dec_point;
}

int check_int_spec(char ch) {
    char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
    int res = 0;
    for (s21_size_t i = 0; i < sizeof(specs); i++) {
        if (specs[i] == ch) {
            res = 1;
            break;
        }
    }
    return res;
}

void prepend_ox(spec flag, char *buff) {
    if (!is_all_zeroes(buff) || flag.spec == 'p') {
        s21_memmove(buff + 2, buff, s21_strlen(buff));
        *buff = '0';
        *(buff + 1) = 'x';
    }
}

int is_all_zeroes(char *buff) {
    int res = 1;
    for (int i = 0; *(buff + i); i++)
        if (*(buff + i) != '0') {
            res = 0;
            break;
        }
    return res;
}

void prepend_mantiss(char *str, int pow, char sign) {
    int len = s21_strlen(str);
    *(str + len) = 'e';
    *(str + len + 1) = sign;
    *(str + len + 3) = pow % 10 + '0';
    pow /= 10;
    *(str + len + 2) = pow % 10 + '0';
    *(str + len + 4) = '\0';
}

void remove_trailing_zeroes(spec flag, char *buff) {
    int len = s21_strlen(buff);
    char *dot = S21_NULL;
    dot = s21_strchr(buff, flag.dec_point);
    if (dot) {
        for (int i = len - 1; *(buff + i) != flag.dec_point; i--) {
            if (*(buff + i) == '0') {
                *(buff + i) = '\0';
            } else {
                break;
            }
        }
        if (!flag.sharp && *(dot + 1) == '\0') *dot = '\0';
    }
}
