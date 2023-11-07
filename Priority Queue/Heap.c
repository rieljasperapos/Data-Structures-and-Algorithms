#include <stdio.h>
#include <stdlib.h>

#define MAX 15

typedef struct {
    int elem[MAX];
    int lastIndx;
} Heap;

void initialize(Heap *H);
void insert(Heap *H, int elem);
void deletemin(Heap *H);
void display(Heap H);

int main() {
    Heap H;

    initialize(&H);
    display(H);

    // 3, 4, 9 
    insert(&H, 3);
    insert(&H, 4);
    insert(&H, 9);
    insert(&H, 6);
    insert(&H, 5);
    insert(&H, 9);
    insert(&H, 10);
    insert(&H, 10);
    insert(&H, 18);
    insert(&H, 7);
    insert(&H, 2);
    display(H);

}

void initialize(Heap *H) {
    int i;
    for (i = 0; i < MAX; i++) {
        H->elem[i] = -1;
    }

    H->lastIndx = -1;
}

void display(Heap H) {
    int i;
    printf("Last index is: %d\n", H.lastIndx);
    if (H.lastIndx == -1) {
        printf("Heap array is empty\n");
    }

    for (i = 0; H.lastIndx != -1 && i <= H.lastIndx; i++) {
        printf("index[%d]: %d\n", i, H.elem[i]);
    }
}

void insert(Heap *H, int elem) {
    if (H->lastIndx < MAX) {
        H->elem[++H->lastIndx] = elem;
        int childIndx = H->lastIndx;

        int child = H->elem[childIndx];
        int parentIndx = (childIndx - 1) / 2;
        int parent = H->elem[parentIndx];

        while (child < parent) {
            int temp = parent;
            printf("PARENT INDEX: %d\n", parentIndx);
            H->elem[parentIndx] = child;
            H->elem[childIndx] = temp;

            childIndx = parentIndx;
            child = H->elem[childIndx];
            parentIndx = (childIndx - 1) / 2;
            parent = H->elem[parentIndx];
        }
    } else {
        printf("Heap is full\n");
    }
}

