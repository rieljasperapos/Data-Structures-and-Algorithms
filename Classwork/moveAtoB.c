#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
}*node;

void initList(node *head) {
    *head = NULL;
}

void insert(node *head, int data) {
    node newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void visualize(node head) {
    if (head == NULL) {
        printf("EMPTY\n");
        return;
    }

    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

void moveAtoB(node *A, node *B) {
    node trav;
    trav = *B;
    while(trav->next != NULL) {
        // printf("%d\n", trav->data);
        trav = trav->next;
    }

    // printf("%d\n", trav->data);
    trav->next = *A;
    *A = NULL;
    
    // printf("%s\n", trav);
}

int main() {
    node headA, headB;
    initList(&headA);
    initList(&headB);

    insert(&headA, 6);
    insert(&headA, 5);
    insert(&headA, 4);

    insert(&headB, 3);
    insert(&headB, 2);
    insert(&headB, 1);

    moveAtoB(&headA, &headB);

    visualize(headA);
    visualize(headB);
    // visualize(headA);
    // visualize(headB);


}