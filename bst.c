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
        exit(1);
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

BST *deleteNode(BST *list, int data) { 

    if (data < list->data.age) {
        list->left = deleteNode(list->left, data);
    } else if (data > list->data.age) {
        list->right = deleteNode(list->right, data);
    } else {

        printf("\n==Deleting %s==\n", list->data.name);
        BST *delete = list;
        // DELETING A LEAF NODE WITH NO CHILDNODES OR ONE CHILD
        if (list->left == NULL) {
            BST *temp = list->right;
            free(delete);
            return temp;
        } else if (list->right == NULL) {
            BST *temp = list->left;
            free(delete);
            return temp;
        }

        // DELETE IF BOTH CHILD NODES ARE PRESENT
        else {
            BST *temp = list->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            list->data = temp->data;
            list->right = deleteNode(list->right, list->data.age);
            printf("\nDATA: %d\n", data);
            // printf("\n%d\n", temp->data.age);
            // printf("%d\n", list->data.age);
            // return list;
        }

    }


    return list;

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

void inorderBST(BST *list) {
    if (list == NULL) {
        return;
    }

    inorderBST(list->left);
    printf("%s - %d - %d - %d - %s\n", list->data.name, list->data.age, list->data.id, list->data.year, list->data.program);
    inorderBST(list->right);
}

void preorderBST(BST *list) {
    if (list == NULL) {
        return;
    }

    printf("%s - %d - %d - %d - %s\n", list->data.name, list->data.age, list->data.id, list->data.year, list->data.program);
    preorderBST(list->left);
    preorderBST(list->right);

}

void postorderBST(BST *list) {
    if (list == NULL) {
        return;
    }

    postorderBST(list->left);
    postorderBST(list->right);
    printf("%s - %d - %d - %d - %s\n", list->data.name, list->data.age, list->data.id, list->data.year, list->data.program);

}

int height(BST *list) {
    if (list == NULL) {
        return 0;
    }

    int lHeight = height(list->left);
    int rHeight = height(list->right);

    return ((lHeight > rHeight) ? lHeight : rHeight) + 1;

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

    BST *searched = searchBST(myBST, 14);
    if (searched != NULL) {
        printf("\nSearched Found\n");
    } else {
        printf("\nSearch not Found\n");
    }
    printf("%s - %d - %d - %d - %s\n", searched->data.name, searched->data.age, searched->data.id, searched->data.year, searched->data.program);

    printf("\nDELETE\n");
    myBST = deleteNode(myBST, 19);
    //myBST = deleteNode(myBST, 69);
    display(myBST);
    BST *searched1 = searchBST(myBST, 14);
    if (searched1 != NULL) {
        printf("\nSearched Found\n");
    } else {
        printf("\nSearch not Found\n");
    }

    printf("INORDER BST DISPLAY\n");
    inorderBST(myBST);
    printf("\nPREORDER BST DISPLAY\n");
    preorderBST(myBST);
    printf("\nPOSTORDER BST DISPLAY\n");
    postorderBST(myBST);

    printf("\nTHE HEIGHT OF THE TREE: %d\n", height(myBST));


    return 0;
}