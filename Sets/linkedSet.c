#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node *link;
} *Node;

void initialize(Node *SET);
void insertSorted(Node *SET, int elem);
void display(Node SET);
Node UNION(Node setA, Node setB);
Node INTERSECTION(Node setA, Node setB);
Node DIFFERENCE(Node setA, Node setB);


int main() {
    Node setA;
    Node setB;
    initialize(&setA);
    initialize(&setB);

    insertSorted(&setA, 2);
    insertSorted(&setA, 3);
    insertSorted(&setA, 1);

    insertSorted(&setB, 6);
    insertSorted(&setB, 3);
    insertSorted(&setB, 5);
    insertSorted(&setB, 4);

    printf("Set A: { ");
    display(setA);
    printf("}");
    printf("\n");
    printf("Set B: { ");
    display(setB);
    printf("}");

    printf("\n");
    Node setC = UNION(setA, setB);
    printf("Set C: { ");
    display(setC);
    printf("}");

    return 0;
}

void initialize(Node *SET) {
    *SET = NULL;
}

void insertSorted(Node *SET, int elem) {
    Node newNode = malloc(sizeof(struct node));

    Node *trav = SET;
    while(*trav != NULL && elem > (*trav)->elem) {
        trav = &(*trav)->link;
    }

    // printf("What is trav ? %s\n", *trav);
    newNode->link = *trav;
    newNode->elem = elem;
    *trav = newNode;
}

void display(Node SET) {
    while (SET != NULL) {
        printf("%d ", SET->elem);
        SET = SET->link;
    }
}

Node UNION(Node setA, Node setB) {
    Node setC = NULL;
    Node tail = NULL;
    
    while (setA != NULL && setB != NULL) {
        Node newNode = malloc(sizeof(struct node));
        
        if (setA->elem < setB->elem) { 
            newNode->elem = setA->elem;
            setA = setA->link;
        } else if (setB->elem < setA->elem) {
            newNode->elem = setB->elem;
            setB = setB->link;
        } else {
            newNode->elem = setA->elem;
            setA = setA->link;
            setB = setB->link;
        }
        
        newNode->link = NULL;
        (setC == NULL) ? (setC = newNode, tail = newNode) : (tail->link = newNode, tail = newNode);
    }

    (setA == NULL) ? (tail->link = setB) : (tail->link = setA);

    return setC;
}


