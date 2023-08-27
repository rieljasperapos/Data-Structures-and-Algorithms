#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char elem;
    struct node *middle;
    struct node *left;
    struct node *right;
} *ternaryTree;

void initTree(ternaryTree *myTree) {
    // write code here
    *myTree = NULL;
}

ternaryTree newNode(char data) {
    ternaryTree newNode = malloc(sizeof(struct node));
    newNode->elem = data;
    newNode->left = newNode->right = newNode->middle = NULL;
    return newNode;
}

void insertString(ternaryTree *myTree, char *string) {
    if (*myTree == NULL) {
        *myTree = newNode(*string);
    }

    // if ((*myTree)->middle == NULL) {
    //     insertString(&(*myTree)->middle, string);
    // }

    // if a character is less than in terms of ascii value go to left
    if (*string < (*myTree)->elem) {
        insertString(&(*myTree)->left, string);
    } else {
    // if a character is greater than in terms of ascii value go to right
        insertString(&(*myTree)->right, string);
    }

    (*myTree)->elem = '\0';

    
}

void display(ternaryTree myTree) {
    while (myTree != NULL) {
        printf("%c\n", myTree->elem);
        myTree = myTree->middle;
    }
}


int main() {
    ternaryTree myTree;
    initTree(&myTree);

    char string[50];
    scanf("%s", &string);

    insertString(&myTree, string);


    display(myTree);


    

    return 0;
}