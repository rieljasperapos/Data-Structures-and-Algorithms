#include <stdio.h>

typedef unsigned char SET;

void initSet(SET *A);
void insert(SET *A, int elem);
void displayBitPattern(SET A);
void displayElement(SET A);
void delete(SET *A, int elem);
SET UNION(SET A, SET B);
SET intersection(SET A, SET B);

int main() {
    SET mySetA;
    SET mySetB;
    initSet(&mySetA);

    // given SET A = {7, 0, 4, 2}
    // {7, 0, 4, 2} 128 64 32 16 8 4 2 1 = 128 + 16 + 4 + 1
    mySetA = 149;

    // Displays the bit pattern of SET A
    displayBitPattern(mySetA);

    // Displays the elements of SET A
    displayElement(mySetA);

    // Insert 3 in SET A
    printf("\n\nInserted 3 in SET A: \n");
    insert(&mySetA, 3);
    displayBitPattern(mySetA);
    displayElement(mySetA);

    // Insert existing element in SET A... Here for ex. 3
    printf("\n\nInserted existing 3 in SET A: \n");
    insert(&mySetA, 3);
    displayBitPattern(mySetA);
    displayElement(mySetA);

    // Delete the element 7 in the SET
    printf("\n\nDeleting 7: \n");
    delete(&mySetA, 7);
    displayBitPattern(mySetA);
    displayElement(mySetA);

    initSet(&mySetB);
    insert(&mySetA, 7);
    insert(&mySetA, 2);
    insert(&mySetB, 6);
    insert(&mySetB, 4);
    insert(&mySetB, 7);
    SET mySetC = UNION(mySetA, mySetB);
    // printf("\n");
    // display(mySetA);
    // printf("\n");
    // // display(mySetB);
    // printf("\n");
    // // display(mySetC);
    
}

void initSet(SET *A) {
    *A = 0;
}

void displayBitPattern(SET A) {
    int size = sizeof(char) * 8;
    for (int i = 0; i < size; i++) {
        if ((A & 1 << i) != 0) {
            printf("Index[%d]: %d\n", i, 1);
        } else {
            printf("Index[%d]: %d\n", i, 0);
        }
    }
}

void displayElement(SET A) {
    int size = sizeof(SET) * 8;
    int i;
    printf("Elements: ");
    for (i = size-1; i >= 0; i--) {
        if ((A & 1 << i) > 0) {
            printf("%d ", i);
        }
    }
}

void insert(SET *A, int elem) {
    *A = *A | 1 << elem;
}

void delete(SET *A, int elem) {
    *A = *A & (~(1 << elem));
}

SET UNION(SET A, SET B) {
    return A | B;
}

SET intersection(SET A, SET B) {
    return A & B;
}