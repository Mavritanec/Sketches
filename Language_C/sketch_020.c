#include <stdio.h>

int factor(int a);

int main() {
    int n;

    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        int res = factor(n) / (factor(i) * factor(n - i));
        printf("%d\n", res);
    }

    return 0;
}

int factor(int a) {
    int fac = 1;
    for (int i = 1; i <= a; i++) {
        fac *= i;
    }
    return fac;
}
