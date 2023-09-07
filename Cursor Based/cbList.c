#include <stdio.h>
#include <string.h>

#define MAX 5
typedef int LIST;

typedef struct {
    char elem;
    int link;
} node;

typedef struct {
    node Nodes[MAX];
    int avail;
} virtualHeap;

virtualHeap initialize() {
    virtualHeap vh;
    int i;
    for (i = 0; i < MAX; i++) {
        vh.Nodes[i].elem = ' ';
        vh.Nodes[i].link = i - 1;
    }

    vh.avail = MAX - 1;

    return vh;
}

int allocSpace(virtualHeap *vh) {
    printf("ALLOC AVAIL: %d\n", vh->avail);
    int retVal = vh->avail;
    if (retVal == -1) {
        printf("NOT ENOUGH SPACE\n");
    } else {
        vh->avail = vh->Nodes[retVal].link;
    }

    return retVal;
}

void deallocSpace(virtualHeap *vh, int index) {
    printf("AVAIL IS: %d\n", vh->avail);
    vh->Nodes[index].link = vh->avail;
    vh->avail = index;
}

void insertFirst(virtualHeap *vh, LIST *L, char elem) {
    int temp = allocSpace(vh);
    if (temp != -1) {
        vh->Nodes[temp].elem = elem;
        vh->Nodes[temp].link = *L;
        *L = temp;
    }
}

void deleteFirstOccurence(virtualHeap *vh, LIST *L, char elem) {
    int trav = *L;
    for (; trav != -1 && vh->Nodes[trav].elem != elem; trav = vh->Nodes[trav].link) {}
    // int currentNode = *L;
    vh->Nodes[(trav)-1].link = vh->Nodes[trav].link;
    printf("MY L IS: %d\n", *L);
    deallocSpace(vh, trav);

}

void displayList(virtualHeap vh, LIST L) {
    for (; L != -1; L = vh.Nodes[L].link) {
        printf("%c ", vh.Nodes[L].elem);
    }
}

int main() {
    virtualHeap myHeap;
    myHeap = initialize();

    LIST L = -1;
    insertFirst(&myHeap, &L, 'C');
    insertFirst(&myHeap, &L, 'S');
    insertFirst(&myHeap, &L, 'U');
    displayList(myHeap, L);

    printf("VALUE OF L: %d\n", L);
    deleteFirstOccurence(&myHeap, &L, 'S');
    printf("\n");
    displayList(myHeap, L);

}