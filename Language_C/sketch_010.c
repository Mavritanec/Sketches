#include <stdio.h>

void print_binary(int val);

int main(void) {
    int val_1 = 255555;
    int val_2 = 255555;

    printf("%d\n", val_1 * val_2);
    print_binary(val_1);
    print_binary(val_2);
    print_binary(val_1 * val_2);

    return 0;
}

void print_binary(int val) {
    printf("Res: ");
    for (int i = sizeof(val) * 8 - 1; i >= 0; i--) {
        printf("%d", val & (1 << i) ? 1 : 0);
    }
    printf("\n");
}
