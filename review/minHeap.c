#include <stdio.h>
#define MAX 10

typedef struct {
  int elems[MAX];
  int lastIndx;
} LIST;

void initialize(LIST *A);
void initializeUnsortedList(LIST *A);
void insert(LIST *A, int elem); // insert to an initially empty heap
void minHeap(LIST *A, int pIndx); // heapify the unsorted list (minHeap)
void maxHeap(LIST *A, int pIndx); // heapify the unsorted list (maxHeap)
void heapify(LIST *A);
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

int getBigChild(LIST L, int pIndx) {
  int retVal = 0;
  int LC = (pIndx * 2) + 1;
  int RC = (pIndx * 2) + 2;
  if (RC < MAX) {
    if (L.elems[RC] > L.elems[LC]) {
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
  int temp = *x;
  *x = *y;
  *y = temp;
}

void heapify(LIST *A) {
  int parentIndx;
  for (parentIndx = (A->lastIndx - 1) / 2; parentIndx >= 0; parentIndx--) {
    // minHeap(A, parentIndx);
    maxHeap(A, parentIndx);
  }
}

// minHeap v2
void minHeap(LIST *A, int pIndx) {
    int smallChildIndx = getSmallChild(*A, pIndx); // Find the smaller child
    while (smallChildIndx < MAX && A->elems[pIndx] > A->elems[smallChildIndx]) { // Loop until POT is satisfied
      swap(&(A->elems[smallChildIndx]), &(A->elems[pIndx])); // swap elements
      pIndx = smallChildIndx;
      smallChildIndx = getSmallChild(*A, pIndx);
    }
}

void maxHeap(LIST *A, int pIndx) {
    int bigChildIndx = getBigChild(*A, pIndx); // Find the bigger child
    while (bigChildIndx < MAX && A->elems[pIndx] < A->elems[bigChildIndx]) { // Loop until POT is satisfied
      swap(&(A->elems[bigChildIndx]), &(A->elems[pIndx])); // swap elements
      pIndx = bigChildIndx;
      bigChildIndx = getBigChild(*A, pIndx);
    }
}

// minHeap v1
// void minHeap(LIST *A, int pIndx) {
//   // Find the parent of the rightmost child
//   int parentIndx;
//   for (parentIndx = (A->lastIndx - 1) / 2; parentIndx >= 0; parentIndx--) {
//     int smallChildIndx = getSmallChild(*A, parentIndx); // Find the small child
//     while (smallChildIndx < MAX && A->elems[parentIndx] > A->elems[smallChildIndx]) { // Loop until POT is satisfied
//       swap(&(A->elems[smallChildIndx]), &(A->elems[parentIndx]));
//       parentIndx = smallChildIndx;
//       smallChildIndx = getSmallChild(*A, parentIndx);
//     }
//   }
// }

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