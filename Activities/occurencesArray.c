#include <stdio.h>
#define MAX 5

typedef struct {
    char elem[MAX];
    int count;
} LIST;

void initList(LIST *list) {
    list->count = 0;
}

void insert(LIST *list, char data) {
    list->elem[list->count++] = data;
}

void display(LIST list) {
    printf("Value of count: %d\n", list.count);
    for (int indx = 0; indx < list.count; indx++) {
        printf("%c ", list.elem[indx]);
    }
}

void removeOccurences(LIST *list, char data) {
    int newIndx = 0;
    for (int indx = 0; indx < list->count; indx++) {
        if (list->elem[indx] != data) {
            list->elem[newIndx++] = list->elem[indx];
        }
    }
    list->count = newIndx;
}

int main() {
    LIST L;
    initList(&L);

    insert(&L, 'A');
    insert(&L, 'B');
    insert(&L, 'C');
    insert(&L, 'A');
    insert(&L, 'C');
    insert(&L, 'B');
    insert(&L, 'D');

    display(L);
    printf("\n");

    removeOccurences(&L, 'A');
    display(L);
    printf("\n");

    removeOccurences(&L, 'C');
    display(L);
    printf("\n");
    
    removeOccurences(&L, 'B');
    display(L);
    printf("\n");

    display(L);

    // printf("Count is: %d\n", L.count);





}