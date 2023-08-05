#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[30];
    int age;
    int id;
    int year;
    char program[10];
} studentDetail;

typedef struct node{
    studentDetail data;
    struct node *left;
    struct node *right;
} BST, *bstPtr;

studentDetail createStudent(char *name, int age, int id, int year, char *program) {
    studentDetail s;
    strcpy(s.name, name);
    s.age = age;
    s.id = id;
    s.year = year;
    strcpy(s.program, program);

    return s;
}

void initBST(bstPtr *tree) {
    *tree = NULL;
}

// bool isEmpty(bstPtr *tree) {
//     return ((*tree) == NULL) ? 1 : 0;
// }

bstPtr addNode(BST *element, studentDetail s) {
    if (element == NULL) {
        bstPtr newNode = malloc(sizeof(BST));
        newNode->data = s;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (s.age < element->data.age) {
        element->left = addNode(element->left, s);
    } else if (s.age > element->data.age) {
        element->right = addNode(element->right, s);
    }

    return element;
}

BST *searchBST(BST *list, int age) {
    if (list == NULL) {
        printf("Tree is empty\n");
        return;
    }

    BST *current = list;
    while (current != NULL) {
        if (current->data.age == age) {
            return current;
        }

        // if the searched age is less than the root age go to the left subtree else go to the right subtree
        if (age < current->data.age) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
}

void display(BST *list) {
    if (list == NULL) {
        printf("NULL\n");
        return;
    } else {
        printf("%s - %d - %d - %d - %s\n", list->data.name, list->data.age, list->data.id, list->data.year, list->data.program);
    }

    printf("\n%s's LEFT ELEMENT: \n", list->data.name);
    display(list->left);
    printf("\n%s's RIGHT ELEMENT: \n", list->data.name);
    display(list->right);
    
}

int main() {
    BST *myBST;
    initBST(&myBST);

    myBST = addNode(myBST, createStudent("Riel", 19, 22105020, 2, "BSCS"));
    myBST = addNode(myBST, createStudent("Ruby", 16, 22105020, 2, "BSCS"));
    myBST = addNode(myBST, createStudent("Jedro", 69, 22105020, 2, "BSCS"));
    myBST = addNode(myBST, createStudent("Aqua", 14, 22105020, 2, "BSCS"));
    myBST = addNode(myBST, createStudent("Arima", 70, 22105020, 2, "BSCS"));
    display(myBST);

    BST *searched;
    searched = searchBST(myBST, 19);
    if (searched != NULL) {
        printf("\nSearched Found\n");
    } else {
        printf("\nSearch not Found\n");
    }
    printf("%s - %d - %d - %d - %s\n", searched->data.name, searched->data.age, searched->data.id, searched->data.year, searched->data.program);

    return 0;
}