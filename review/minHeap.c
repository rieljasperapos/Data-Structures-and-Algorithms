#include <stdio.h>
#define MAX 10

typedef struct {
  int elems[MAX];
  int lastIndx;
} LIST;

void initialize(LIST *A);
void initializeUnsortedList(LIST *A);
void insert(LIST *A, int elem); // insert to an initially empty heap
void heapify(LIST *A); // heapify the unsorted list
void displayHeap(LIST L);

int main() {
  LIST myHeap;
  // initialize(&myHeap);
  initializeUnsortedList(&myHeap);
  // int tempList[MAX] = {35, 33, 42, 10, 14, 19, 27, 44, 26, 31};
  heapify(&myHeap);
  // int indx;
  // for (indx = 0; indx < MAX; indx++) {
  //   insert(&myHeap, tempList[indx]);
  // }

  displayHeap(myHeap);
  

  return 0;
}

void initializeUnsortedList(LIST *A) {
  int tempList[MAX] = {35, 33, 42, 10, 14, 19, 27, 44, 26, 31};
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    A->elems[indx] = tempList[indx];
  }
  A->lastIndx = MAX - 1;
}

void initialize(LIST *A) {
  A->lastIndx = -1;
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    A->elems[indx] = -1;
  }
}

int getSmallChild(LIST L, int pIndx) {
  int retVal = 0;
  int LC = (pIndx * 2) + 1;
  int RC = (pIndx * 2) + 2;
  if (RC < MAX) {
    if (L.elems[RC] < L.elems[LC]) {
       retVal = RC;
    } else {
      retVal = LC;
    }
  } else {
    retVal = LC;
  }

  return retVal;
}

void swap(int *x, int *y) {
  // TODO: Swap element here
  printf("child: %d parent: %d\n", *x, *y);
  int temp = *x;
  *x = *y;
  *y = temp;
}

void heapify(LIST *A) {
  // Find the parent of the rightmost child
  int parentIndx = (A->lastIndx - 1) / 2;
  for (; parentIndx >= 0; parentIndx--) {
    int smallChildIndx = getSmallChild(*A, parentIndx);
    while (smallChildIndx < MAX && A->elems[parentIndx] > A->elems[smallChildIndx]) {
      swap(&(A->elems[smallChildIndx]), &(A->elems[parentIndx]));
      parentIndx = smallChildIndx;
      smallChildIndx = getSmallChild(*A, parentIndx);
    }
  }
}

void insert(LIST *A, int elem) {
  // TODO: Insert to an initially empty heap
  if ((A->lastIndx - 1) < MAX) {
    A->elems[++A->lastIndx] = elem;
    int parent, child;
    for (parent = (A->lastIndx - 1) / 2, child = A->lastIndx; A->elems[child] < A->elems[parent]; child = parent, parent = (child - 1) / 2) {
      swap(&(A->elems[parent]), &(A->elems[child]));
    }
  }
}

void displayHeap(LIST L) {
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    printf("index[%d]: %d\n",indx, L.elems[indx]);
  }
}