#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID;
    char LN[16], FN[24], MI;
    char course[8];
    int yearLevel;
}Studrec;

typedef struct node {
    Studrec stud;
    struct node *link;
}*StudList;

Studrec createStud(int ID, char *LN, char *FN, char MI, char *course, int year) {
    Studrec s;
    s.ID = ID;
    strcpy(s.LN, LN);
    strcpy(s.FN, FN);
    strcpy(s.course, course);
    s.MI = MI;
    s.yearLevel = year;

    return s;
    
}

void initList(StudList *L) {
    *L = NULL;
}

void insertFirstUnique(StudList *L, Studrec S) {
    StudList *trav;
    for (trav = L; *trav != NULL && (*trav)->stud.ID != S.ID; trav = &(*trav)->link) {}
    if (*trav == NULL) {
        StudList newNode = malloc(sizeof(struct node));
        newNode->stud = S;
        newNode->link = *L;
        *L = newNode;
    }
}

Studrec deleteElement(StudList *L, int ID) {
    StudList *trav;
    Studrec empty = {0, "XXXX", "XXXX", 'X', 'XXXX', 0};
    Studrec element;
    for (trav = L; *trav != NULL && (*trav)->stud.ID != ID; trav = &(*trav)->link) {}
    if (*trav == NULL) {
        element = empty;
    } else {
        StudList delete = *trav;
        element = (*trav)->stud;
        *trav = (*trav)->link;
        free(delete);
    }
    return element;
}

void visualize(StudList L) {
    while (L != NULL) {
        printf("%d - %s, %s %c.\n", L->stud.ID, L->stud.LN, L->stud.FN, L->stud.MI);
        L = L->link;
    }
}

int main() {
    StudList L;
    initList(&L);

    insertFirstUnique(&L, createStud(1, "Apos", "Riel", 'A', "BSCS", 2));
    insertFirstUnique(&L, createStud(69, "Pasco", "Jericho", 'A', "BSCS", 3));
    insertFirstUnique(&L, createStud(42, "Morales", "Stanleigh", 'A', "BSCS", 1));
    insertFirstUnique(&L, createStud(1, "Apos", "Riel", 'A', "BSCS", 2));
    insertFirstUnique(&L, createStud(6, "Apos", "Riel", 'A', "BSCS", 2));

    visualize(L);

    printf("To DELETE: \n");
    Studrec delete;
    delete = deleteElement(&L, 42);
    printf("%d - %s, %s %c. - %s - %d\n", delete.ID, delete.LN, delete.FN, delete.MI, delete.course, delete.yearLevel);

    // deleteElement(&L, 42);
    visualize(L);
}