#include <stdio.h>
#include <stdlib.h>

#define MAX 6

// definition of set
typedef int SET[MAX];

SET *UNION(SET A, SET B);
void insert(SET set, int num);
void delete(SET set, int num);

int main() {
    SET A = {1, 1, 1, 0, 0, 0};
    SET B = {0, 0, 0, 1, 1, 1};

    printf("This is SET A: \n");
    for (int i = 0; i < MAX; i++) {
        printf("Index[%d]: %d\n", i, A[i]);
    }

    printf("\n");

    printf("This is SET B: \n");
    for (int i = 0; i < MAX; i++) {
        printf("Index[%d]: %d\n", i, B[i]);
    }

    printf("\n");
    SET *C = UNION(A, B);
    printf("Union of SET A and B\n");
    for (int i = 0; i < MAX; i++) {
        printf("index[%d]: %d\n", i, (*C)[i]);
    }

    insert(A, 5);
    insert(A, 3);
    delete(A, 3);

    printf("\n");
    printf("This is SET A: \n");
    for (int i = 0; i < MAX; i++) {
        printf("Index[%d]: %d\n", i, A[i]);
    }

    return 0;
}

SET *UNION(SET A,  SET B) {
    SET *temp = malloc(sizeof(int) * MAX);

    for (int indx = 0; indx < MAX; indx++) {
        (*temp)[indx] = A[indx] | B[indx];
    }

    return temp;
}

void insert(SET set, int num) {
        set[num] = 1;
}

void delete(SET set, int num) {
    set[num] = 0;
}