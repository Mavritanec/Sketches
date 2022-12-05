#include <stdio.h>

#define BUFF_SIZE 64

int main() {
    int code[] = {99, 100, 101, 69, 102, 103, 71, 105,
                  110, 111, 112, 115, 117, 120, 88, 37};

    for (int i = 0; i < 16; i++) printf("%d:\t%c\n", code[i], code[i]);

    return 0;
}
