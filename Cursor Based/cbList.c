#include <stdio.h>
#include <string.h>

#define MAX 5
typedef int CLIST;

typedef struct {
    int id;
    char fname[20];
    char lname[20];
    char program[8];
    int year;
} Studrec;

typedef struct {
    Studrec stud;
    int link;
} node;

typedef struct {
    node Nodes[MAX];
    int avail;
} virtualHeap;

virtualHeap initialize();
Studrec newStudent(int id, char *fname, char *lname, char *program, int year);
int allocSpace(virtualHeap *vh);
void deallocSpace(virtualHeap *vh, int index);
void insertFirst(virtualHeap *vh, CLIST *L, Studrec elem);
void insertLast(virtualHeap *vh, CLIST *L, Studrec elem);
void deleteFirstOccurence(virtualHeap *vh, CLIST *L, int id);
void displayList(virtualHeap vh, CLIST L);

int main() {
    virtualHeap myHeap;
    myHeap = initialize();
    CLIST L = -1;

    insertFirst(&myHeap, &L, newStudent(22105020, "Riel", "Apos", "BSCS", 2));
    insertFirst(&myHeap, &L, newStudent(12345678, "Ruby", "Hoshino", "BSPSYCH", 1));
    insertFirst(&myHeap, &L, newStudent(17105020, "Aqua", "Hoshino", "BSCS", 2));
    displayList(myHeap, L);

    deleteFirstOccurence(&myHeap, &L, 17105020);
    printf("\nAfter Delete\n");
    displayList(myHeap, L);

    insertLast(&myHeap, &L, newStudent(16523123, "Jonathan", "Abdul", "BSCpE", 1));
    displayList(myHeap, L);

    return 0;
}

virtualHeap initialize() {
    virtualHeap vh;
    int i;
    for (i = 0; i < MAX; i++) {
        vh.Nodes[i].stud = newStudent(0, "XXXX", "XXXX", "XXXX", 0);
        vh.Nodes[i].link = i - 1;
    }

    vh.avail = MAX - 1;
    return vh;
}

Studrec newStudent(int id, char *fname, char *lname, char *program, int year) {
    Studrec s;
    s.id = id;
    strcpy(s.fname, fname);
    strcpy(s.lname, lname);
    strcpy(s.program, program);
    s.year = year;

    return s;
}

int allocSpace(virtualHeap *vh) {
    int retVal = vh->avail;
    if (retVal == -1) {
        printf("NOT ENOUGH SPACE\n");
    } else {
        vh->avail = vh->Nodes[retVal].link;
    }

    return retVal;
}

void deallocSpace(virtualHeap *vh, int index) {
    if (index > -1 && index < MAX) {
        vh->Nodes[index].link = vh->avail;
        vh->avail = index;
    }
}

void insertFirst(virtualHeap *vh, CLIST *L, Studrec elem) {
    int temp = allocSpace(vh);
    if (temp != -1) {
        vh->Nodes[temp].stud = elem;
        vh->Nodes[temp].link = *L;
        *L = temp;
    }
}

void insertLast(virtualHeap *vh, CLIST *L, Studrec elem) {
    int temp = allocSpace(vh);
    CLIST *trav = L;
    if (temp != -1) {
        for (; *trav != -1; trav = &vh->Nodes[*trav].link) {}
        *trav = temp;
        vh->Nodes[temp].stud = elem;
        vh->Nodes[temp].link = -1;
    }
}

void deleteFirstOccurence(virtualHeap *vh, CLIST *L, int id) {
    CLIST *trav = L;
    for (; *trav != -1 && vh->Nodes[*trav].stud.id != id; trav = &vh->Nodes[*trav].link) {}
    if (*trav != -1) {
        CLIST temp = *trav;
        *trav = vh->Nodes[temp].link;
        deallocSpace(vh, temp);
    }
}

void displayList(virtualHeap vh, CLIST L) {
    printf("%5s    | %15s | %10s | %s\n", "ID", "NAME", "PROGRAM", "YEAR");
    printf("---------------------------------------------\n");
    for (; L != -1; L = vh.Nodes[L].link) {
        printf("%8d %18s %10s %5d\n" , vh.Nodes[L].stud.id, vh.Nodes[L].stud.fname, vh.Nodes[L].stud.program, vh.Nodes[L].stud.year);
    }
}