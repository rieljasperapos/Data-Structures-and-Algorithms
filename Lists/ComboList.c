#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char FN[20];
    char LN[20];
    char MN[20];
} nameType;

typedef struct {
    nameType name;
    char ID[10];
    char course[8];
    int yrLevel;
} studRec;

// linked list
typedef struct node {
    studRec stud;
    struct node *sLink;
} *studLink;

// array
typedef struct arr {
    studRec stud[MAX];
    int studCount;
} studArray;


// Combo List
typedef struct List {
    studLink IT; // BSIT list
    studArray CS; //BSCS list
} *ComboList;

void initLink(studLink *A);
void insertSortedLink(studLink *A, studRec stud);
nameType newName(char *FN, char *LN, char *MN);
studRec newStud(nameType name, char *ID, char *course, int yrLevel);
void display(studLink L);
ComboList createComboList(studLink *A);
void displayComboListArray(ComboList L);
void displayComboListLink(ComboList L);


int main() {
    studLink S;
    initLink(&S);
    ComboList myComboList;

    studRec stud = newStud(newName("Riel", "Apos", "Alilin"), "22105020", "BSCS", 2);
    studRec stud1 = newStud(newName("Aqua", "Hoshino", "Alilin"), "12345678", "BSCS", 2);
    studRec stud2 = newStud(newName("Ruby", "Hoshino", "Alilin"), "21105020", "BSIT", 1);
    studRec stud3 = newStud(newName("Kana", "Arima", "Alilin"), "32105020", "BSIT", 3);
    studRec stud4 = newStud(newName("Jedro", "Morales", "Balmes"), "42105020", "BSCS", 1);
    studRec stud5 = newStud(newName("Josh", "Jake", "Goddamn"), "22125831", "BSIT", 1);
    insertSortedLink(&S, stud);
    insertSortedLink(&S, stud1);
    insertSortedLink(&S, stud2);
    insertSortedLink(&S, stud3);
    insertSortedLink(&S, stud4);
    insertSortedLink(&S, stud5);

    myComboList = createComboList(&S);

    printf("LINKED LIST\n");
    displayComboListLink(myComboList);
    printf("\nARRAY LIST\n");
    displayComboListArray(myComboList);
    printf("\nORIGINAL LIST\n");
    display(S);

    return 0;
}

void initLink(studLink *A) {
    *A = NULL;
}

nameType newName(char *FN, char *LN, char *MN) {
    nameType name;
    strcpy(name.FN, FN);
    strcpy(name.LN, LN);
    strcpy(name.MN, MN);

    return name;
}

studRec newStud(nameType name, char *ID, char *course, int yrLevel) {
    studRec s;
    s.name = name;
    strcpy(s.ID, ID);
    strcpy(s.course, course);
    s.yrLevel = yrLevel;

    return s;
}

void insertSortedLink(studLink *A, studRec stud) {
    studLink *trav;
    for (trav = A; *trav != NULL && strcmp((*trav)->stud.ID, stud.ID) > 0; trav = &(*trav)->sLink) {}
    studLink temp = malloc(sizeof(struct node));
    if (temp != NULL) {
        temp->stud = stud;
        temp->sLink = *trav;

        *trav = temp;
    } else {
        printf("Memory Allocation Failed\n");
    }
}

ComboList createComboList(studLink *A) {
    studLink *trav = A;
    ComboList L = malloc(sizeof(struct List));
    L->CS.studCount = 0;
    L->IT = NULL;
    while (*trav != NULL) {
        if (strcmp((*trav)->stud.course, "BSCS") == 0) {
            L->CS.stud[L->CS.studCount++] = (*trav)->stud;
            *trav = (*trav)->sLink;
        } else if (strcmp((*trav)->stud.course, "BSIT") == 0) {
            studLink temp = malloc(sizeof(struct node));
            temp->stud = (*trav)->stud;
            temp->sLink = L->IT;
            L->IT = temp;

            *trav = (*trav)->sLink;
        } else {
            trav = &(*trav)->sLink;
        }
    }

    return L;
}

void display(studLink L) {
    while (L != NULL) {
        printf("%s, %s %s | %s\n", L->stud.ID, L->stud.name.FN, L->stud.name.LN, L->stud.course);
        L = L->sLink;
    }
}

void displayComboListArray(ComboList L) {
    int indx;
    for (indx = 0; indx < L->CS.studCount; indx++) {
        printf("Stud[%d]: %s, %s %s | %s\n", indx, L->CS.stud[indx].ID, L->CS.stud[indx].name.FN, L->CS.stud[indx].name.LN, L->CS.stud[indx].course);
    }
}

void displayComboListLink(ComboList L) {
    while (L->IT != NULL) {
        printf("%s, %s %s | %s\n", L->IT->stud.ID, L->IT->stud.name.FN, L->IT->stud.name.LN, L->IT->stud.course);
        L->IT = L->IT->sLink;
    }
}

