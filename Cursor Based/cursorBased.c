#include <stdio.h>
#include <string.h>

#define MAX 5
typedef int List;

typedef struct {
    char name[30];
    int id;
    char course[8];
} Studrec;

typedef struct {
    Studrec data;
    int next;
} studList;

typedef struct {
    studList elems[MAX];
    int avail;
} virtualHeap;

Studrec newStudent(char *name, int id, char *course) {
    Studrec stud;
    strcpy(stud.name, name);
    stud.id = id;
    strcpy(stud.course, course);

    return stud;
}

virtualHeap newVirtualHeap() {
    virtualHeap vh;
    int i;
    for (i = 0; i < MAX; i++) {
        vh.elems[i].data = newStudent("XXXX", 0, "XXXX");
        vh.elems[i].next = i-1;
    }

    vh.avail = MAX - 1;

    return vh;
}

int allocSpace(virtualHeap *vh) {
    int retVal = vh->avail;

    if (retVal != -1) {
        vh->avail = vh->elems[vh->avail].next;;
    }

    return retVal;
}

void insertFront(virtualHeap *vh, List *L, Studrec stud) {
    List temp = allocSpace(vh);
    if (temp == -1) {
        printf("NOT ENOUGH SPACE CANNOT INSERT %s\n", stud.name);
    } else {
        vh->elems[temp].data = stud;
        vh->elems[temp].next = *L;
        *L = temp;
    }
}

void visualize(virtualHeap vh) {
    printf("INDEX | NAME | ID | COURSE\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d %10s %4d %6s\n", i, vh.elems[i].data.name, vh.elems[i].data.id, vh.elems[i].data.course);
    }
}

int main() {
    virtualHeap myHeap = newVirtualHeap();
    List myList = -1;

    printf("MY AVAIL VH IS: %d\n", myHeap.avail);

    insertFront(&myHeap, &myList, newStudent("Riel", 1, "BSCS"));
    visualize(myHeap);
    insertFront(&myHeap, &myList, newStudent("Jedro", 2, "BSCS"));
    visualize(myHeap);
    insertFront(&myHeap, &myList, newStudent("Aqua", 2, "BSCS"));
    visualize(myHeap);
    insertFront(&myHeap, &myList, newStudent("Arima", 2, "BSCS"));
    visualize(myHeap);
    insertFront(&myHeap, &myList, newStudent("Ruby", 2, "BSCS"));
    visualize(myHeap);
    insertFront(&myHeap, &myList, newStudent("Ethan", 2, "BSCS"));
    visualize(myHeap);

}