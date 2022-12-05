// вывод массива змейкой по часовой стрелке

#include <stdio.h>

int main() {
    int n;

    if (scanf("%d", &n) == 1 && n > 0) {
        int matrix[n][n];

        int count = 1;
        int dir_ball = 0;
        int x_b = 0;
        int y_b = 0;

        int left = 0;
        int right = n - 1;

        // заполнение массива змейкой по часовой стрелке
        while (count != (n * n + 1)) {
            matrix[y_b][x_b] = count;
            count++;
            
            if (dir_ball == 0) {  // move right
                if (x_b == right) {
                    y_b++;
                    dir_ball = 1;
                } else x_b++;
            } else if (dir_ball == 1) {  // move left
                if (x_b == left) {
                    y_b++;
                    dir_ball = 0;
                } else x_b--;
            }
        }

        // вывод массива
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%.3d", matrix[i][j]);
                if (j < n - 1) printf(" ");
            }
            if (i < n - 1) printf("\n");
        }

        printf("\n");
    } else printf("n/a");

    return 0;
}
