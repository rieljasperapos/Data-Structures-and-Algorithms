#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

typedef struct node {
  int elem;
  struct node *link;
} *LIST;

typedef LIST listArr[SIZE];
typedef int Vertex;

void dfs(Vertex V, int *mark, listArr L, listArr T);
void initListArr(listArr A);
void insertSorted(listArr L, int elem, int v);
void displayListArr(listArr L);

int main() {
  listArr L;
  listArr tree;
  initListArr(tree);
  initListArr(L);
  insertSorted(L, 1, 0);
  insertSorted(L, 2, 0);

  insertSorted(L, 2, 1);
  insertSorted(L, 3, 1);
  
  insertSorted(L, 0, 2);

  insertSorted(L, 2, 3);
  insertSorted(L, 0, 3);

  insertSorted(L, 6, 4);
  insertSorted(L, 5, 4);

  insertSorted(L, 1, 5);

  insertSorted(L, 5, 6);
  insertSorted(L, 3, 6);
  // displayListArr(L);
  printf("Traversal:\n");
  int mark[SIZE] = {0};
  dfs(1, mark, L, tree);
  dfs(4, mark, L, tree);
  printf("\nTree created:");
  displayListArr(tree);

  return 0;
}

void displayList(LIST L) {
  LIST trav;
  for (trav = L; trav != NULL; trav = trav->link) {
    printf("%d ", trav->elem);
  }
}

void initListArr(listArr A) {
  int indx;
  for (indx = 0; indx < SIZE; indx++) {
    A[indx] = NULL;
  }
}

void insertSorted(listArr L, int elem, int v) {
  LIST temp = (LIST)malloc(sizeof(struct node));
  if (temp != NULL) {
    LIST *trav;
    for (trav = &L[v]; *trav != NULL && (*trav)->elem < elem; trav = &(*trav)->link) {}
    temp->elem = elem;
    temp->link = *trav;
    *trav = temp;
  }
}

void displayListArr(listArr L) {
  int indx;
  for (indx = 0; indx < SIZE; indx++) {
    printf("\nL[%d]: ", indx);
    displayList(L[indx]);
  }
}

void dfs(Vertex V, int *mark, listArr L, listArr T) {
  mark[V] = 1;
  LIST trav;
  for (trav = L[V]; trav != NULL; trav = trav->link) {
    if (mark[trav->elem] == 0) {
      LIST temp = (LIST)malloc(sizeof(struct node));
      if (temp != NULL) {
        temp->elem = trav->elem;
        temp->link = T[V];
        T[V] = temp;
      }
      dfs(trav->elem, mark, L, T);
    }
  }
  if (trav == NULL) {
    return;
  }
}