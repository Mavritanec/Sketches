#include <stdio.h>
#include <stdlib.h>

#define HEIGHT_MAX 100
#define WIDTH_MAX 100

void input_menu(int *point);
void input_size(int *height, int *width);
void static_matrix(int height, int width, int buff[height][width], int *ch);
void static_output(int height, int width, int buff[height][width]);
void dyn_1_matrix(int **buff, int height, int width, int *ch);
void dyn_2_matrix(int **buff, int height, int width, int *ch);
void dyn_3_matrix(int **buff, int height, int width, int *ch);
void dyn_output(int **buff, int height, int width);

int main() {
    int menu, height_size, width_size;
    int **mass = NULL;

    input_menu(&menu);
    if (menu == -1) exit(0);

    input_size(&height_size, &width_size);
    if (height_size == -1) exit(0);

    int flag = 1;
    switch(menu) {
        case 1: {
            int st_mass[height_size][width_size];
            static_matrix(height_size, width_size, st_mass, &flag);
            if (flag == 0) exit(0);

            static_output(height_size, width_size, st_mass);
            break;
        }
        case 2: {
            mass = malloc(height_size * width_size * sizeof(int) + height_size * sizeof(int *));

            if (mass != NULL) {
                dyn_1_matrix(mass, height_size, width_size, &flag);
            } else {
                printf("The malloc function did't work correctly");
            }
            if (flag == 0) exit(0);

            dyn_output(mass, height_size, width_size);
            free(mass);
            break;
        }
        case 3: {
            mass = malloc(height_size * sizeof(int *));

            if (mass != NULL) {
                dyn_2_matrix(mass, height_size, width_size, &flag);
            } else {
                printf("The malloc function did't work correctly");
            }
            if (flag == 0) exit(0);

            dyn_output(mass, height_size, width_size);
            free(*mass);
            free(mass);
            break;
        }
        case 4: {
            mass = malloc(height_size * sizeof(int *));

            if (mass != NULL) {
                dyn_3_matrix(mass, height_size, width_size, &flag);
            } else {
                printf("The malloc function did't work correctly");
            }
            if (flag == 0) exit(0);

            dyn_output(mass, height_size, width_size);
            for (int i = 0; i < height_size; i++) free(mass[i]);
            free(mass);
            break;
        }
    }

    return 0;
}

void input_menu(int *item) {
    char z;

    printf("Menu:\n"
           "  1 - static matrix\n"
           "  2 - dynamic matrix type 1\n"
           "  3 - dynamic matrix type 2\n"
           "  4 - dynamic matrix type 3\n");
    printf("\nEnter menu item: ");

    if (!(scanf("%d%c", item, &z) == 2 && z == '\n' && *item > 0 && *item < 5)) {
        *item = -1;
        printf("Incorrect item menu\n");
    }
}

void input_size(int *height, int *width) {
    char w, z;

    printf("\nEnter the height and width of the matrix: ");

    if (!(scanf("%d%c%d%c", height, &w, width, &z) == 4 &&
          (w == ' ' || w == '\n') && (z == ' ' || z == '\n') &&
          *height > 0 && *height <= HEIGHT_MAX &&
          *width > 0  && *width <= WIDTH_MAX)) {
        *height = -1;
        printf("Incorrect input of matrix height or width\n");
    }
}

void static_matrix(int height, int width, int buff[height][width], int *ch) {
    char z;
    *ch = 1;

    printf("\nEnter the matrix elements: ");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(scanf("%d%c", &buff[i][j], &z) == 2 && (z == '\n' || z == ' '))) {
                *ch = 0;
                printf("Incorrect input\n");
            }
        }
    }
}

void static_output(int height, int width, int buff[height][width]) {
    printf("\nThe matrix:\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", buff[i][j]);
            if (j < width - 1) printf("\t");
        }
        if (i < height - 1) printf("\n");
    }

    printf("\n");
}

void dyn_1_matrix(int **buff, int height, int width, int *ch) {
    char z;
    *ch = 1;

    int *ptr = (int *)(buff + height);
    for (int i = 0; i < height; i++) buff[i] = ptr + width * i;

    printf("\nEnter the matrix elements: ");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(scanf("%d%c", &buff[i][j], &z) == 2 && (z == '\n' || z == ' '))) {
                *ch = 0;
                printf("Incorrect input\n");
            }
        }
    }
}

void dyn_2_matrix(int **buff, int height, int width, int *ch) {
    char z;
    *ch = 1;

    int *arr = malloc (height * width * sizeof(int));
    if (arr == NULL) {
        printf("The malloc function did't work correctly");
        exit(0);
    }

    for (int i = 0; i < height; i++) buff[i] = arr + width * i;

    printf("\nEnter the matrix elements: ");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(scanf("%d%c", &buff[i][j], &z) == 2 && (z == '\n' || z == ' '))) {
                *ch = 0;
                printf("Incorrect input\n");
            }
        }
    }
}

void dyn_3_matrix(int **buff, int height, int width, int *ch) {
    char z;
    *ch = 1;

    for (int i = 0; i < height; i++) {
        buff[i] = malloc (width * sizeof(int));
        if (buff[i] == NULL) {
            printf("The malloc function did't work correctly");
            exit(0);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(scanf("%d%c", &buff[i][j], &z) == 2 && (z == '\n' || z == ' '))) {
                *ch = 0;
            }
        }
    }
}

void dyn_output(int **buff, int height, int width) {
    printf("\nThe matrix:\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", buff[i][j]);
            if (j < width - 1) printf("\t");
        }
        if (i < height - 1) printf("\n");
    }

    printf("\n");
}
