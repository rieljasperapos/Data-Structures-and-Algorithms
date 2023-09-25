#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node *link;
} *SET;

void initialize(SET *mySet);
void insertSorted(SET *mySet, int elem);
void display(SET mySet);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);


int main() {
    SET setA;
    SET setB;
    initialize(&setA);
    initialize(&setB);

    insertSorted(&setA, 2);
    insertSorted(&setA, 3);
    insertSorted(&setA, 1);
    // insertSorted(&setA, 4);
    // insertSorted(&setA, 5);

    insertSorted(&setB, 6);
    insertSorted(&setB, 3);
    insertSorted(&setB, 5);
    insertSorted(&setB, 4);
    // insertSorted(&setB, 7);

    printf("Set A: { ");
    display(setA);
    printf("}");
    printf("\n");
    printf("Set B: { ");
    display(setB);
    printf("}");

    printf("\n");
    SET unionSet = UNION(setA, setB);
    printf("Set UNION: { ");
    display(unionSet);
    printf("}");

    printf("\n");
    SET intersectionSet = INTERSECTION(setA, setB);
    printf("Set INTERSECTION: { ");
    display(intersectionSet);
    printf("}");
    printf("\n");

    printf("\n");
    SET differenceSet = DIFFERENCE(setA, setB);
    printf("Set DIFFERENCE: { ");
    display(differenceSet);
    printf("}");
    printf("\n");



    return 0;
}

void initialize(SET *mySet) {
    *mySet = NULL;
}

void insertSorted(SET *mySet, int elem) {
    SET newNode = malloc(sizeof(struct node));

    SET *trav = mySet;
    while(*trav != NULL && elem > (*trav)->elem) {
        trav = &(*trav)->link;
    }

    // printf("What is trav ? %s\n", *trav);
    newNode->link = *trav;
    newNode->elem = elem;
    *trav = newNode;
}

void display(SET mySet) {
    while (mySet != NULL) {
        printf("%d ", mySet->elem);
        mySet = mySet->link;
    }
}

SET UNION(SET A, SET B) {
    SET setC = NULL;
    SET tail = NULL;
    
    while (A != NULL && B != NULL) {
        SET newNode = malloc(sizeof(struct node));
        if (A->elem < B->elem) { 
            newNode->elem = A->elem;
            A = A->link;
        } else if (B->elem < A->elem) {
            newNode->elem = B->elem;
            B = B->link;
        } else {
            newNode->elem = A->elem;
            A = A->link;
            B = B->link;
        }

        newNode->link = NULL;
        (setC == NULL) ? (setC = newNode, tail = newNode) : (tail->link = newNode, tail = newNode);
    }

    (A == NULL) ? (tail->link = B) : (tail->link = A);

    return setC;
}

SET INTERSECTION(SET A, SET B) {
    SET setIntersection = NULL;
    SET tail = NULL;

    while (A != NULL && B != NULL) {
        SET newNode = malloc(sizeof(struct node));
        if (A->elem == B->elem || A->elem < B->elem) {
            newNode->elem = A->elem;
            A = A->link;
        } else {
            B = B->link;
        }

        (setIntersection == NULL) ? (setIntersection = newNode, tail = newNode) : (tail->link = newNode, tail = newNode);
    }
}

SET DIFFERENCE(SET A, SET B) {
    SET setDiff = NULL;
    SET tail = NULL;

    while (A != NULL) {
        if (B == NULL || A->elem < B->elem) {
            SET newNode = malloc(sizeof(struct node));
            newNode->elem = A->elem;
            newNode->link = NULL;
            (setDiff == NULL) ? (setDiff = newNode, tail = newNode) : (tail->link = newNode, tail = newNode);
            A = A->link;
        } else if (A->elem == B->elem) {
            A = A->link;
            B = B->link;
        } else {
            B = B->link;
        }
    }

    return setDiff;
}

// SET DIFFERENCE(SET A, SET B) {
//     SET setDiff = NULL;
//     SET tail = NULL;

//     while (A != NULL && B != NULL) {
//         SET newNode = malloc(sizeof(struct node));
//         if (A->elem < B->elem) {
//             newNode->elem = A->elem;
//             newNode->link = NULL;
//             A = A->link;
//         } else if (B->elem < A->elem) {
//             B = B->link;
//         } else {
//             A = A->link;
//             B = B->link;
//         }

//         printf("My NODE is %d\n", newNode->elem);
//         if (newNode->elem == 0 ) {
//             setDiff = A;
//         }  else {
//             (setDiff == NULL && newNode->elem == 0) ? (setDiff = newNode, tail = newNode) : (tail->link = newNode, tail = newNode);
//         }
//     }


//     return setDiff;
// }




