#include <stdio.h>

#define MAX 20
#define EMPTY 0
#define DELETED -1

typedef int LIST;

typedef struct node {
    int elem;
    int link;
} Node;

typedef struct {
    Node data[MAX];
    int avail;
} VirtualHeap;

VirtualHeap initVirtualHeap();
void insert(VirtualHeap *vh, LIST *myList, int elem);
void delete(VirtualHeap *vh, int elem);
int hash(int elem);
int allocSpace(VirtualHeap *vh);
void deallocSpace(VirtualHeap *vh, int index);
void displayPrimeDatas(VirtualHeap vh);
void displaySynonymsData(VirtualHeap vh);


int main() {
    VirtualHeap myVH;
    myVH = initVirtualHeap();
    printf("MY AVAIL IN MAIN IS: %d\n", myVH.avail);
    LIST myList = -1;

    insert(&myVH, &myList, 13);
    insert(&myVH, &myList, 19);
    insert(&myVH, &myList, 14);
    insert(&myVH, &myList, 33);
    insert(&myVH, &myList, 19);
    insert(&myVH, &myList, 10);
    insert(&myVH, &myList, 23);

    delete(&myVH, 13);
    delete(&myVH, 33);

    insert(&myVH, &myList, 43);
    insert(&myVH, &myList, 53);
    insert(&myVH, &myList, 63);
    displayPrimeDatas(myVH);
    printf("\n");
    displaySynonymsData(myVH);

    return 0;
}

int hash(int elem) {
    return elem % 10;
}

VirtualHeap initVirtualHeap() {
    VirtualHeap vh;
    int i;

    // 0-9 Prime Data Area 
    for (i = 0; i < MAX-10; i++) {
        vh.data[i].elem = EMPTY;
    }

    //10-19 Synonyms
    for (i = MAX-10; i < MAX; i++) {
        vh.data[i].elem = 0;
        vh.data[i].link = i+1;
    }
    vh.data[MAX-1].link = -1;

    vh.avail = MAX-10;
    return vh;
}

void deallocSpace(VirtualHeap *vh, int index) {
    if (index >= 0 && index < MAX) {
        vh->data[index].link = vh->avail;
        vh->avail = index;
    }
}

int allocSpace(VirtualHeap *vh) {
    // printf("MY AVAIL IN ALLOCSPACE IS: %d\n", vh->avail);
    int retVal = vh->avail;
    if (retVal != -1) {
        vh->avail = vh->data[retVal].link;
    }
    return retVal;
}


void insert(VirtualHeap *vh, LIST *myList, int elem) {
    int index = hash(elem);
    // printf("MY INDEX IS: %d\n", index);

    if (vh->data[index].elem == EMPTY || vh->data[index].elem == DELETED) {
        if (vh->data[index].elem == EMPTY) {
            vh->data[index].link = *myList;
        }  
        vh->data[index].elem = elem;
    } else {
        int avail = allocSpace(vh);
        vh->data[avail].elem = elem;
        vh->data[avail].link = vh->data[index].link;
        vh->data[index].link = avail;
    }
}

void delete(VirtualHeap *vh, int elem) {
    int hashIndex = hash(elem);
    if (vh->data[hashIndex].elem != DELETED) {
        vh->data[hashIndex].elem = DELETED;
    } else {
        int *trav = &(vh->data[hashIndex].link);
        for (; *trav != -1 && vh->data[*trav].elem != elem; trav = &(vh->data[*trav].link)) {}
        if (*trav != -1) {
            int temp = *trav;
            *trav = vh->data[temp].link;
            deallocSpace(vh, temp);
        }
    }

}

void displayPrimeDatas(VirtualHeap vh) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        printf("Index[%d]: %d Link: %d\n", i, vh.data[i].elem, vh.data[i].link);
    }
}

void displaySynonymsData(VirtualHeap vh) {
    int i = 0;
    for (i = 10; i < MAX; i++) {
        printf("Index[%d]: %d Link: %d\n", i, vh.data[i].elem, vh.data[i].link);
    }
}