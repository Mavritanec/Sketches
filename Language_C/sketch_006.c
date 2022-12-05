#include <stdio.h>

#if defined(__APPLE__) // || defined(__MACH__)
#define OS 'M'
#elif defined(__linux__)
#define OS 'L'
#else
#define OS 'L'
#endif

int main() {
    printf("Operation system: %c.\n", OS);
    return 0;
}
