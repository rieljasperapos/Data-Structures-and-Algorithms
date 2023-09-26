#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
    int elem;
    struct node *link;
} *LIST;

typedef LIST DICTIONARY[MAX];


void initialize(DICTIONARY A);
void display(DICTIONARY A);
void displayIndex(LIST A);
void insert(DICTIONARY A, int elem);
int hash(int elem);

int main() {
    DICTIONARY myDict;
    initialize(myDict);
    display(myDict);
    insert(myDict, 10);
    insert(myDict, 20);
    insert(myDict, 60);
    displayIndex(myDict[0]);

    return 0;
}

void initialize(DICTIONARY A) {
    int i;
    for (i = 0; i < MAX; i++) {
        A[i] = NULL;
    }
}

int hash(int elem) {
    return elem % 10;
}

void insert(DICTIONARY A, int elem) {
    LIST newNode = malloc(sizeof(struct node));
    newNode->elem = elem;
    newNode->link = NULL;
    int index = hash(elem);
    
    printf("My index is: %d\n", index);
    if (A[index] == NULL) {
        A[index] = newNode;
    } else {
        // Insert front logic for O(1)
        LIST trav = A[index];
        newNode->link = trav;
        A[index] = newNode;

        // Dictionary *trav = A[index];
        // while (*trav != NULL) {
        //     trav = &(*trav)->link;
        // }
        // *trav = newNode;
    }
}

// for checking each index of the dictionary if elements are properly inserted
void displayIndex(LIST A) {
    int i;
    while (A != NULL) {
        printf("%d\n", A->elem);
        A = A->link;
    }
}


// just to check the dictionary if it was initialized correctly
void display(DICTIONARY A) {
    int i;
    for (i = 0; i < MAX; i++) {
        printf("%p\n", A[i]);
    }
}