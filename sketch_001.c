#include <stdio.h>

#define BUFF_SIZE 64


int main() {
    char *token_string = "15 12 14...";

    char s[BUFF_SIZE / 4];
    char c;
    int i1, i2;
    float fp;

    sscanf(token_string, "%s", s);
    sscanf(token_string, "%c", &c);
    sscanf(token_string, "%d %d", &i1, &i2);
    sscanf(token_string, "%f", &fp);

    printf("%s\n", s);
    printf("%c\n", c);
    printf("%d %d\n", i1, i2);
    printf("%f\n", fp);
  
    return 0;
}
