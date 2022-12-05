#include <stdio.h>

// argc - количество аргументов (нулевой аргумент название самого исполняемого файла)
// argv - массив из string'ов, содержащий эти аргументы
int main(int argc, char **argv) {

    if (argc > 1) {
        printf("Args count: %d\n", argc);
        for (int i = 1; i < argc; i++) printf("Arg: %s\n", *(argv + i));
        printf("\n");

         for (int i = 1; i < argc; i++) {
            FILE *file = fopen(*(argv + i), "r");
            // fopen (в случае успеха) возвращает дескриптор файла, это беззнаковое целое число
            // в случае неудачи, возвращает NULL
            printf("Error num: %u\n", file);
            if (file) fclose(file);
        }
    } else {
        printf("Not enough arguments\n");
    }

    return 0;
}
