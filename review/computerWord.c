#include <stdio.h>

typedef unsigned char SET;

void displayBitPattern(SET S);
void addElement(SET *A, int element);
void deleteElement(SET *A, int element);
void displayElements(SET S);

/*

ADT Based on SETS:
ADT UID

*/
SET setUnion(SET A, SET B);
SET setIntersection(SET A, SET B);
SET setDifference(SET A, SET B);

int main() {
    SET A = 149; // elements = { 7, 4, 2, 0}
    SET B = 6; // elements = { 2, 1 }

    // A = 1 0 0 1 0 1 0 1
    // B = 0 0 0 0 0 1 1 0
    SET UNION = setUnion(A, B);
    printf("UNION\n");
    displayBitPattern(UNION);
    displayElements(UNION);

    printf("\n\n");

    SET INTERSECTION = setIntersection(A, B);
    printf("INTERSECTION\n");
    displayBitPattern(INTERSECTION);
    displayElements(INTERSECTION);

    printf("\n\n");

    SET DIFFERENCE = setDifference(A, B);
    printf("DIFFERENCE\n");
    displayBitPattern(DIFFERENCE);
    displayElements(DIFFERENCE);

/*
    printf("\n\n");
    displayBitPattern(A);
    addElement(&A, 3);
    printf("After Adding\n");
    displayBitPattern(A);
    deleteElement(&A, 3);
    printf("After deleting\n");
    displayBitPattern(A);

    // display elements
    displayElements(A);

*/

    return 0;
}

void displayBitPattern(SET S) {
    int size = sizeof(char) * 8;
    // printf("Size: %d\n", size);
    int indx;
    for (indx = size-1; indx >= 0; indx--) {
        if ((S & 1 << indx) != 0) {
            printf("[%d]: %d\n", indx, 1);
        } else {
            printf("[%d]: %d\n", indx, 0);
        }
    }
}

void displayElements(SET S) {
    int size = sizeof(char) * 8;
    int indx;
    printf("{ ");
    for (indx = 0; indx < size; indx++) {
        if ((S & 1 << indx) != 0) {
            printf("%d", indx);
            if (indx < size - 1) {
                printf(", ");
            }
        }
    }
    printf(" }");
}

void addElement(SET *A, int element) {
    *A = *A | 1 << element;
}

void deleteElement(SET *A, int element) {
    // 1 0 0 1 1 1 0 1
    // 0 0 0 0 1 0 0 0
    // 1 1 1 1 0 1 1 1
    *A = *A & ~(1 << element);
}

SET setUnion(SET A, SET B) {
    return A | B;
}

SET setIntersection(SET A, SET B) {
    return A & B;
}

SET setDifference(SET A, SET B) {
    return A & ~B;
}