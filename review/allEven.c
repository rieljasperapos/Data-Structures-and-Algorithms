#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 6

int *findAllEven(int arr[], int size);

int main() {
  int arr[MAX] = {1,2,3,6,5,11};
  int *evens = findAllEven(arr, MAX);

  return 0;
}

int *findAllEven(int arr[], int size) {
  int indx, count = 1;
  int *retArray;
  int temp[size];

  for (indx = 0; indx < size; indx++) {
    if (arr[indx] % 2 == 0) {
      temp[count++] = arr[indx];
    }
  }
  temp[0] = count - 1;
  retArray = malloc(sizeof(int));
  memcpy(retArray, temp, sizeof(int) * count);

  return retArray;
}