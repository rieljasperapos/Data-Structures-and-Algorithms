#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
  int label;
  struct node *LC;
  struct node *RC;
} *BST;

typedef enum { TRUE, FALSE } Boolean;

void displayBST(BST T);
Boolean Member(BST T, int elem);
void initBST(BST *T);
void insertNode(BST *T, int elem);
void deleteNode(BST *T, int elem);
int min(BST T);
int max(BST T);


int main() {
  BST myTree;
  initBST(&myTree);
  int tempArr[MAX] = {15, 11, 18, 4, 14, 17, 20, 11, 16, 13};
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    insertNode(&myTree, tempArr[indx]);
  }
  displayBST(myTree);
  printf("\n");
  printf("MIN: %d\n", min(myTree));
  printf("MAX: %d\n", max(myTree));

  deleteNode(&myTree, 11);
  deleteNode(&myTree, 18);
  displayBST(myTree);

  Boolean found = Member(myTree, 17);
  found == TRUE ? printf("FOUND") : printf("NOT FOUND");

}

void initBST(BST *A) {
    *A = NULL;
}

void insertNode(BST *T, int elem) {
    BST temp = (BST)malloc(sizeof(struct node));
    if (temp != NULL) {
        BST *trav;
        for (trav = T; *trav != NULL && elem != (*trav)->label;) {
          if (elem < (*trav)->label) {
            trav = &(*trav)->LC;
          } else {
            trav = &(*trav)->RC;
          }
            // (elem < (*trav)->label) ? trav = &(*trav)->LC : trav = &(*trav)->RC;
        }
        if (*trav == NULL) {
            temp->label = elem;
            temp->RC = NULL;
            temp->LC = NULL;
            *trav = temp;
        }
    }
}

void deleteNode(BST *T, int elem) {
    BST *trav;
    for (trav = T; *trav != NULL && (*trav)->label != elem;) {
        if (elem < (*trav)->label) {
          trav = &(*trav)->LC;
        } else {
          trav = &(*trav)->RC;
        }
        // (elem < (*trav)->label) ? trav = &(*trav)->LC : trav = &(*trav)->RC;
    }
    if (*trav != NULL) {
        BST temp = *trav;
        if (temp->LC == NULL) {
            *trav = temp->RC;
        } else if (temp->RC == NULL) {
            *trav = temp->LC;
        } else {
            BST *successor;
            for (successor = &temp->RC; (*successor)->LC != NULL; successor = &(*successor)->LC) {}
            BST tempSuccessor = *successor;
            temp->label = tempSuccessor->label;
            *successor = tempSuccessor->RC;
            free(tempSuccessor);
        }
    }
    
}

Boolean Member(BST T, int elem) {
    Boolean found;
    BST trav;
    for (trav = T; trav != NULL && elem != trav->label;) {
      
      if (elem < trav->label) {
        trav = trav->LC;
      } else {
        trav = trav->RC;
      }
    }
    if (trav != NULL) { 
      found = TRUE;
    } else { 
      found = FALSE;
    }
    
    return found;
}

void displayBST(BST T) {
    if (T == NULL) {
        return;
    }
    displayBST(T->LC);
    printf("%d ", T->label);
    displayBST(T->RC);
}

int min(BST T) {
    BST trav;
    int retVal = -9999; // terminal value
    for (trav = T; trav != NULL && trav->LC != NULL; trav = trav->LC) {} // Loop until it reaches the lowest level leftmost child
    if (T != NULL) {
      retVal = trav->label;
    }
    
    return retVal;
}

int max(BST T) {
    BST trav;
    int retVal = -9999; // terminal value
    for (trav = T; trav != NULL && trav->RC != NULL; trav = trav->RC) {} // Loop until it reaches the lowest level leftmost child
    if (T != NULL) {
      retVal = trav->label;
    }
    
    return retVal;
}