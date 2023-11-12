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
void heapSort(Heap *H) ;
void display(Heap H);
void swap(Heap *H, int a, int b);
int getSmallChild(Heap H, int parentIndx);

int main() {
    Heap H;

    initialize(&H);
    display(H);
    // int parentIndx = getParent(3);
    // printf("Parent index is: %d\n", parentIndx);

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

    heapSort(&H);
    printf("\nHeap sort\n");
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

void swap(Heap *H, int a, int b) {
    int temp = H->elem[a];
    H->elem[a] = H->elem[b];
    H->elem[b] = temp;
}

void insert(Heap *H, int elem) {
    if (H->lastIndx < MAX) {
        H->elem[++H->lastIndx] = elem;
        int childIndx = H->lastIndx;
        int parentIndx = (childIndx - 1) / 2;

        int child = H->elem[childIndx];
        int parent = H->elem[parentIndx];

        while (child < parent) {
            swap(H, parentIndx, childIndx);

            childIndx = parentIndx;
            child = H->elem[childIndx];
            parentIndx = (childIndx - 1) / 2;
            parent = H->elem[parentIndx];
        }
    } else {
        printf("Heap is full\n");
    }
}

int getSmallChild(Heap H, int parentIndx) {
    int LChild = (parentIndx * 2) + 1;
    int RChild = (parentIndx * 2) + 2;

    return (H.elem[LChild] < H.elem[RChild] ? LChild : RChild);

}

void heapSort(Heap *H) {
    int oldLast = H->lastIndx;
    while (H->lastIndx != -1) {
        deletemin(H);
    }
    H->lastIndx = oldLast;
}

void deletemin(Heap *H) {
    int root = 0;
    int last = H->lastIndx;
    swap(H, root, last);
    H->lastIndx--;

    int parentIndx = root;
    int childIndx = getSmallChild(*H, parentIndx);

    int parent = H->elem[parentIndx];
    int child = H->elem[childIndx];

    while (child < parent && childIndx < H->lastIndx) {
        swap(H, parentIndx, childIndx);
        parentIndx = childIndx;
        childIndx = getSmallChild(*H, parentIndx);

        parent = H->elem[parentIndx];
        child = H->elem[childIndx];
    }
}




