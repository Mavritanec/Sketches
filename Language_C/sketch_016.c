#include <stdio.h>
#include <stdlib.h>

struct door {
    int id;
    int status;
};

struct node {
    struct node* next;
    struct door* elem;
};

struct node* init(struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);

int main() {
    struct door door_1;
    door_1.id = 13;
    door_1.status = 3;

    struct door door_2;
    door_2.id = 23;
    door_2.status = 6;

    struct door door_3;
    door_3.id = 33;
    door_3.status = 9;

    struct node* node_1 = init(&door_1);

    printf("%d %d\n", door_1.id, door_1.status);
    printf("%d %d\n", node_1->elem->id, node_1->elem->status);
    printf("%p\n", node_1->next);

    struct node* node_2 = add_door(node_1, &door_2);
    struct node* node_3 = add_door(node_2, &door_3);

    printf("%p\n", node_1->next);
    printf("%p\n", node_2->next);
    printf("%p\n", node_3->next);
    printf("%d %d\n", node_2->elem->id, node_2->elem->status);

    struct node* ans_node;
    ans_node = find_door(23, node_1);

    printf("%d %d\n", ans_node->elem->id, ans_node->elem->status);

    remove_door(node_2, node_1);
    printf("%p\n", node_1->next);
    printf("%p\n", node_3->next);
  
    return 0;
}

struct node* init(struct door* door) {
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->elem = door;

    return new_node;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->elem = door;
    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    while (root->next) {
        if (root->elem->id == door_id) {
            break;
        } else {
            root = root->next;
        }
    }
    return root;
}

struct node* remove_door(struct node* elem, struct node* root) {
    while (root->next != elem) root = root->next;
    root->next = elem->next;
    free(elem);
    return root;
}
