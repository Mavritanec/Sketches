#include <stdio.h>


int main(int argc, char **argv) {

    if (argc == 1) {
//      char ch;
        int ch;
        while ((ch = getc(stdin)) != EOF) putc(ch, stdout);
    }

    return 0;
}
