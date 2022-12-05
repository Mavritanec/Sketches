#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFF_SIZE 64

int mass_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

char mass_2[][BUFF_SIZE] = {
    "1",
    "abc",
    "aabbcc",
    "version",
    "help",
    " 1 2 3 ",
    "show help",
    "",
    "sample code"
};

int main(void) {
    size_t mass_size = sizeof(mass_1);
    size_t elem_size = sizeof(int);

    printf("Number of elements in mass_1: %d\n", mass_size / elem_size);

    printf("\n");
    mass_size = sizeof(mass_2);
    elem_size = BUFF_SIZE;

    printf("Number of elements in mass_2: %d\n", mass_size / elem_size);

    size_t smb_size = sizeof(char);

    for (uint8_t i = 0; i < mass_size / elem_size; i++) {
        char *line = mass_2[i];
        size_t line_size = strlen(mass_2[i]);

        printf("Line %2d, size: %2d: %s\n", i + 1, line_size, line);
    }

    return 0;
}
