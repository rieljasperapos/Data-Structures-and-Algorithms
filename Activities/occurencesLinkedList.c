#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char elem;
    struct node *next;
} *LIST;

void initList(LIST *list) {
    *list = NULL;
}

void insert(LIST *list, char data) {
    LIST newNode = malloc(sizeof(struct node));
    newNode->elem = data;
    newNode->next = *list;
    *list = newNode;
}

void visualize(LIST list) {
    for (; list != NULL; list = list->next) {
        printf("%c ", list->elem);
    }
}

void removeOccurences(LIST *list, char elem) {
    LIST *trav = list;
    while (*trav != NULL) {
        if ((*trav)->elem == elem) {
            LIST delete = *trav;
            *trav = (*trav)->next;
            free(delete);
        } else {
            trav = &(*trav)->next;
        }
    }

    // for (trav = list; *trav != NULL && (*trav)->elem == elem; *trav = (*trav)->next){
    //     LIST delete = *trav;
    //     free(delete);

    // }
}

int main() {
    LIST L;
    initList(&L);

    insert(&L, 'A');
    insert(&L, 'B');
    insert(&L, 'A');
    insert(&L, 'C');
    insert(&L, 'D');
    insert(&L, 'D');
    insert(&L, 'B');

    printf("Before removing\n");
    visualize(L);

    removeOccurences(&L, 'A');
    removeOccurences(&L, 'B');
    removeOccurences(&L, 'D');
    printf("\nAfter removing\n");
    visualize(L);



}