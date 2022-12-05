#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

struct door {
    int id;
    int status;
};

void initialize_doors(struct door* doors);
void print_doors(struct door* doors);

int main() {
    struct door doors[DOORS_COUNT];
    
    initialize_doors(doors);
    print_doors(doors);

    return 0;
}

void initialize_doors(struct door* doors) {
    srand(time(0)); 
    
    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void print_doors(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%.2d %d\n", doors[i].id, doors[i].status);
    }
}
