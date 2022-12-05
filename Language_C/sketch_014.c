#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main() {
    printf("Start program...\n");

    char string_1[200];
    char string_2[200];
    wchar_t str_1[5] = {'b', 'y', 'e'};
    wchar_t str_2[5] = {'g', 'o', 'o', 'd'};

    int res_1 = sprintf(string_1, "|%s|%3s|%-4s|%5.s|%5.2s|%3.*s|%*.*s|%*s|%3ls|%5.5ls|%.3s|",
                        "hello", "WorlD", "Adobe", "Good bye", "DeEp BoOm", -3, "Follow", -10, 5,
                        "bye", -5, "system", str_1, str_2, "abcdefg");
    printf("%d: %s\n", res_1, string_1);

    printf("End program...\n");
    return 0;
}
