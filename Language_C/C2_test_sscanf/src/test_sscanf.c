#include <stdio.h>
#include "s21_string.h"
#include "s21_sscanf.h"

int main(void) {
    setlocale(LC_ALL, "");

    printf("\nStart program...\n\n");


    char *input_str = "";
    char *format_str = "%o";

    unsigned int val1;
    unsigned int val2;

    int res1 = s21_sscanf(input_str, format_str, &val1);
    int res2 = sscanf(input_str, format_str, &val2);
    printf("%d: %o\n", res1, val1);
    printf("%d: %o\n", res2, val2);


    printf("\nEnd program...\n\n");

    return 0;
}

/*
START_TEST(octal_empty) {
    uint32_t a1, a2;
    const char str[] = "";
    const char fstr[] = "%o";
    int res1 = s21_sscanf(str, fstr, &a1);
    int res2 = sscanf(str, fstr, &a2);
    ck_assert_int_eq(res1, res2);
} END_TEST
*/


/*

*/


/*

*/
