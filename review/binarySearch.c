#include <stdio.h>
#define MAX 10

typedef struct {
  int elems[MAX];
  int count;
} arrList;

int binarySearch(arrList A, int elem); // returns -1 if the element is not found, and if found return the element
void insertSorted(arrList *A, int elem);
void initialize(arrList *A);
void displayArray(arrList L);

int main() {
  arrList arr;
  initialize(&arr);
  int tempArr[MAX] = {5, 6, 1, 4, 3, 2, 9, 8, 7, 10};
  int indx;
  for (indx = 0; indx < MAX; indx++) {
    insertSorted(&arr, tempArr[indx]);
  }
  displayArray(arr);
  printf("Elem found: %d \n", binarySearch(arr, 2));


  return 0;
}

void initialize(arrList *A) {
  A->count = 0;
}

void insertSorted(arrList *A, int elem) {
  int indx;
  for (indx = A->count - 1; indx >= 0 && A->elems[indx] > elem && A->count != MAX; indx--) {
    A->elems[indx + 1] = A->elems[indx];
  }
  A->elems[indx + 1] = elem;
  A->count++;
}

int binarySearch(arrList A, int elem) {
  int retVal;
  int upper = A.count - 1;
  int lower = 0;
  int mid = lower + (upper - lower) / 2;
  printf("mid: %d\n", mid);
  for (; A.elems[mid] != elem && lower <= upper; mid = lower + (upper - lower) / 2) {
    if (elem < A.elems[mid]) {
      upper = mid - 1;
    } else {
      lower = mid + 1;
    }
  }
  (lower <= upper) ? (retVal = A.elems[mid]) : (retVal = -1);
  return retVal;
}