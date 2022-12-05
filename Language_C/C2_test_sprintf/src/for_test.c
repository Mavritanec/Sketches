/* "Copyright 2022 <sesamema sesamema@student.21-school.ru>" */

#include <stdio.h>
#include <locale.h>
#include "s21_string.h"
#include "s21_sprintf.h"

int main(void) {
    setlocale(LC_ALL, "");

    char string_1[128];
    char string_2[128];

    printf("\nStart program...\n\n");


    char *input_string = "|%s|%3s|%-4s|%5.s|%5.2s|%3.*s|%*.*s|%*s|%3ls|%5.5ls|%.3s|";
    wchar_t w_ch_1[] = L"森我爱菠萝";
    wchar_t w_ch_2[] = L"森我爱菠萝";

    int res_1 = sprintf(string_1, input_string, "hello", "WorlD", "Adobe", "Good bye", "DeEp BoOm", -3, "Follow",
                    10, 5, "bye", -5, "system", w_ch_1, w_ch_2, "abcdefg");
    printf("%d: %s\n", res_1, string_1);
    int res_2 = s21_sprintf(string_2, input_string, "hello", "WorlD", "Adobe", "Good bye", "DeEp BoOm", -3, "Follow",
                    10, 5, "bye", -5, "system", w_ch_1, w_ch_2, "abcdefg");
    printf("%d: %s\n", res_2, string_2);


    printf("\nEnd program...\n\n");

    return 0;
}


/*
START_TEST(s21_sprintf_test_2) {
    char str1[512];
    char str2[512];
    wchar_t str_1[] = L"森我爱菠萝";
    wchar_t str_2[] = L"森我爱菠萝";
//    wchar_t str_1[] = L"bye";
//    wchar_t str_2[] = L"good";
    int res_1 = sprintf(str1,
                    "|%s|%3s|%-4s|%5.s|%5.2s|%3.*s|%*.*s|%*s|%3ls|%5.5ls|%.3s|",
                    "hello", "WorlD", "Adobe", "Good bye", "DeEp BoOm", -3, "Follow",
                    10, 5, "bye", -5, "system", str_1, str_2, "abcdefg");
    int res_2 = sprintf(str2,
                    "|%s|%3s|%-4s|%5.s|%5.2s|%3.*s|%*.*s|%*s|%3ls|%5.5ls|%.3s|",
                    "hello", "WorlD", "Adobe", "Good bye", "DeEp BoOm", -3, "Follow",
                    10, 5, "bye", -5, "system", str_1, str_2, "abcdefg");
*/
