#include <stdio.h>
#include <stdlib.h>

typedef char String[30];

typedef struct node {
    int elem;
    struct node *left;
    struct node *right;
}tree, *treePtr;

treePtr createNode(int data) {
    treePtr newNode = malloc(sizeof(tree));
    if (newNode == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }
    newNode->elem = data;

    return newNode;
}

treePtr insertNode() {
    int choice;
    String menu[2] = {"Press 1 to add", "Press 0 if not"};
    for (int i = 0; i < 2; i++) {
        printf("%s\n", menu[i]);
    } 
    scanf("%d", &choice);

    if (choice == 0) {
        return NULL;
    } else {
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        treePtr temp = createNode(data);

        printf("Inserting node %d\n", temp->elem);

        // Insert at left using recursion
        printf("Inserting %d's left subtree\n", temp->elem);
        temp->left = insertNode();
        printf("Inserting %d's right subtree\n", temp->elem);
        temp->right = insertNode();

        return temp;
    }
}

int height(treePtr myTree) {
    int lHeight;
    int rHeight;
    if (myTree == NULL) {
        return 0;
    }

    lHeight = height(myTree->left);
    rHeight = height(myTree->right);

    return ((lHeight > rHeight) ? lHeight : rHeight) + 1;
}

void visualize(treePtr myTree) {
    if (myTree == NULL) {
        printf("NULL\n");
        return;
    } else {
        printf("%d\n", myTree->elem);
    }

    printf("%d's left subtree\n", myTree->elem);
    visualize(myTree->left);
    printf("%d's right subtree\n", myTree->elem);
    visualize(myTree->right);
}

int main() {
    treePtr myTree;
    // initTree(&myTree);

    myTree = insertNode();
    printf("\n");
    visualize(myTree);
    printf("The height of the binary tree: %d\n", height(myTree));



}