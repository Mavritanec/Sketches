#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 8
#define WIGTH 8

void output(int matrix[HEIGHT][WIGTH]);
void new_step(int matrix[HEIGHT][WIGTH], int new_matrix[HEIGHT][WIGTH]);

int main() {
    int mat[HEIGHT][WIGTH] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 1, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1, 0, 0, 0, 0},
                              {0, 1, 1, 1, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};

    int new_mat[HEIGHT][WIGTH];

    output(mat);
    new_step(mat, new_mat);
    printf("\n");
    output(new_mat);
    return 0;
}

void output(int matrix[HEIGHT][WIGTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIGTH; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void new_step(int matrix[HEIGHT][WIGTH], int new_matrix[HEIGHT][WIGTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIGTH; j++) {
            int status = 0;
            for (int n = i - 1; n < i + 2; n++) {
                for (int m = j - 1; m < j + 2; m++) {
                    if (n == i && m == j) continue;
                    int y = n;
                    int x = m;
                    if (x < 0) x = HEIGHT - 1;
                    if (x > 24) x = 0;
                    if (y < 0) y = WIGTH - 1;
                    if (y > 24) y = 0;

                    if (matrix[y][x] == 1) status = status + 1;
                }
            }

            if (matrix[i][j] == 0 && status == 3) {
                new_matrix[i][j] = 1;
            } else {
                new_matrix[i][j] = 0;
            }

            // Почему не отрабатывает этот IF???

            if (matrix[i][j] == 1 && (status == 2 || status == 3)) {
                new_matrix[i][j] = 1;
            } else {
                new_matrix[i][j] = 0;
            }

            printf("y=%d x=%d s=%d c=%d n=%d\n", i, j, status, matrix[i][j], new_matrix[i][j]);
        }
        // printf("%d ", matrix[i][j]);
    }
    // printf("\n");
}
