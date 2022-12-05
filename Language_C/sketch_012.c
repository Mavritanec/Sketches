#include <stdio.h>

int main() {
    char string[24];

    sprintf(string, "I eating in %d PM", 11);

    printf(string);
    printf("\n%s\n", string);

    return 0;
}
