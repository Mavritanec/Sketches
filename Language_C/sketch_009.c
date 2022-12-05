#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* mass = NULL;
    int count = 0;
    int num;

    do {
        printf("Input number (0 - exit): ");
        scanf("%d", &num);

        if (num) {
            count++;

            mass = (int*) realloc(mass, count * sizeof(int));

            if (mass) mass[count - 1] = num;
        }
    } while (num);

//  работать не будет (всегда будет делить 8 (размер int*) на 4 (размер int))
//  int len = sizeof(mass) / sizeof(int);
//  printf("Massive size: %d, elements count: %d\n", sizeof(mass), len);

    printf("Massive with %d elements: [", count);
    for (int i = 0; i < count; i++) {
        printf("%d", mass[i]);
        if (i != count - 1) printf(", ");
    }
    printf("]\n");

    for (int i = 0; i < count; i++) printf("%d element in massive is: %d\n", i, mass[i]);

    free(mass);
    return 0;
}
