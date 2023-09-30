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
void displayDictionary(DICTIONARY A);
void insert(DICTIONARY A, int elem);
void delete(DICTIONARY A, int elem);
int hash(int elem);

int main() {
    DICTIONARY myDict;
    initialize(myDict);
    display(myDict);
    insert(myDict, 10);
    insert(myDict, 20);
    insert(myDict, 60);
    insert(myDict, 11);
    insert(myDict, 12);
    insert(myDict, 14);
    insert(myDict, 24);
    insert(myDict, 8);

    delete(myDict, 10);
    displayIndex(myDict[0]);
    displayDictionary(myDict);

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
    
    if (A[index] == NULL) {
        A[index] = newNode;
    } else {
        // Insert front logic for O(1)
        LIST trav = A[index];
        newNode->link = trav;
        A[index] = newNode;
    }
}

void delete(DICTIONARY A, int elem) {
    int hashIndex = hash(elem);
    if (A[hashIndex] == NULL) {
        printf("EMPTY NO VALUES FOUND\n");
    }
    LIST *trav = &A[hashIndex];
    for(; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->link) {}
    LIST temp = *trav;
    *trav = (*trav)->link;
    free(temp);
}


// for checking each index of the dictionary if elements are properly inserted
void displayIndex(LIST A) {
    for (; A != NULL; A = A->link) {
        printf("%d\n", A->elem);
    }
}


// just to check the dictionary if it was initialized correctly
void display(DICTIONARY A) {
    int i;
    for (i = 0; i < MAX; i++) {
        printf("%p\n", A[i]);
    }
}

// Display the dictionary and the element assigned to its index
void displayDictionary(DICTIONARY A) {
    int indx;
    for (indx = 0; indx < MAX; indx++) {
        LIST trav = A[indx];
        printf("index[%d]: ", indx);
        for (; trav != NULL; trav = trav->link) {
            printf("%d -> ", trav->elem);
        }
        printf("NULL");
        printf("\n");
    }
}