#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x2D

typedef struct
{
    char FN[20];
    char MN[20];
    char LN[20];
} nameType;

typedef struct
{
    char ID[10];
    nameType name;
    char course[8];
    int yrLevel;
} studRec;

typedef struct node
{
    studRec stud;
    struct node *slink;
} *studList;

typedef struct
{
    nameType sName;
    char ID[10];
} studInfo;

typedef struct
{
    studInfo data[MAX];
    int studCnt;
} studHeap;

void initList(studList *L);
void insertSorted(studList *L, studRec newStud);
void displayList(studList L);
nameType newName(char *FN, char *MN, char *LN);
studRec newStud(char *ID, nameType studName, char *course, int yrLevel);
void swapStud(studInfo *x, studInfo *y);
int getBigChild(studHeap myStudHeap, int parentIndx);
void displayInfoHeap(studHeap myHeap);
studHeap createInfoHeap(studList *L, char *course);

int main()
{
    studList myStudList;
    initList(&myStudList);

    studRec myStud = newStud("69", newName("Riel", "Alilin", "Apos"), "BSCS", 2);
    studRec myStud1 = newStud("50", newName("John", "Alilin", "Apos"), "BSCS", 2);
    studRec myStud2 = newStud("21", newName("Jasper", "Alilin", "Apos"), "BSIS", 1);
    studRec myStud3 = newStud("16", newName("Gab", "Alilin", "Apos"), "BSCS", 3);
    studRec myStud4 = newStud("11", newName("Josh", "Alilin", "Apos"), "BSCS", 2);
    studRec myStud5 = newStud("45", newName("Aqua", "Alilin", "Apos"), "BSCS", 2);
    studRec myStud6 = newStud("99", newName("Jeric", "Alilin", "Apos"), "BSCS", 2);
    studRec myStud7 = newStud("20", newName("Jan", "Alilin", "Apos"), "BSCS", 2);
    // printf("Name: %s, %s %s\nCourse: %s\nYear: %d\n", myStud.name.LN, myStud.name.FN, myStud.name.MN, myStud.course, myStud.yrLevel);
    insertSorted(&myStudList, myStud);
    insertSorted(&myStudList, myStud4);
    insertSorted(&myStudList, myStud1);
    insertSorted(&myStudList, myStud2);
    insertSorted(&myStudList, myStud3);
    insertSorted(&myStudList, myStud5);
    insertSorted(&myStudList, myStud6);
    insertSorted(&myStudList, myStud7);
    displayList(myStudList);

    studHeap myStudHeap;
    myStudHeap = createInfoHeap(&myStudList, "BSCS");
    printf("\nREMOVED YEAR 2:\n");
    displayList(myStudList);
    printf("MY INFO HEAP:\n");
    displayInfoHeap(myStudHeap);

    return 0;
}

void initList(studList *L)
{
    *L = NULL;
}

void insertSorted(studList *L, studRec newStud)
{
    studList newStudNode = malloc(sizeof(struct node));
    studList *trav;
    if (newStudNode != NULL)
    {
        for (trav = L; *trav != NULL && (*trav)->stud.yrLevel < newStud.yrLevel; trav = &(*trav)->slink)
        {
        }
        newStudNode->stud = newStud;
        newStudNode->slink = *trav;
        *trav = newStudNode;
    }
    else
    {
        printf("Memory Allocation failed\n");
    }
}

void displayList(studList L)
{
    while (L != NULL)
    {
        printf("Year: %d\n", L->stud.yrLevel);
        L = L->slink;
    }
}

void displayInfoHeap(studHeap myHeap) {
    int indx;
    for (indx = 0; indx < myHeap.studCnt; indx++) {
        printf("Stud[%d]: %s, %s\n", indx, myHeap.data[indx].ID, myHeap.data[indx].sName.FN, myHeap.data[indx]);
    }
}

nameType newName(char *FN, char *MN, char *LN)
{
    nameType studName;
    strcpy(studName.FN, FN);
    strcpy(studName.MN, MN);
    strcpy(studName.LN, LN);

    return studName;
}

studRec newStud(char *ID, nameType studName, char *course, int yrLevel)
{
    studRec stud;
    strcpy(stud.ID, ID);
    stud.name = studName;
    strcpy(stud.course, course);
    stud.yrLevel = yrLevel;

    return stud;
}

void swapStud(studInfo *x, studInfo *y)
{
    studInfo temp = *x;
    *x = *y;
    *y = temp;
}

int getBigChild(studHeap myStudHeap, int parentIndx) {
    int LC = (parentIndx * 2) + 1;
    int RC = (parentIndx * 2) + 2;
    int child;

    if (RC < myStudHeap.studCnt) {
        if (strcmp(myStudHeap.data[LC].ID, myStudHeap.data[RC].ID) > 0) {
            child = LC;
        } else {
            child = RC;
        }
    } else {
        child = LC;
    }

    return child;
}

studHeap createInfoHeap(studList *L, char *course)
{
    studList *trav = L;
    studList temp;
    studInfo extractedInfo;
    studHeap myInfoHeap;
    myInfoHeap.studCnt = 0;

    // removed year level 2
    while (*trav != NULL)
    {
        if ((*trav)->stud.yrLevel == 2 && strcmp((*trav)->stud.course, course) == 0)
        {
            printf("%s, %s | %d\n", (*trav)->stud.name.FN, (*trav)->stud.name.LN, (*trav)->stud.yrLevel);
            temp = *trav;
            strcpy(extractedInfo.ID, temp->stud.ID);
            extractedInfo.sName = temp->stud.name;
            myInfoHeap.data[myInfoHeap.studCnt++] = extractedInfo;
            *trav = (*trav)->slink;
        }
        else
        {
            trav = &(*trav)->slink;
        }
    }

    for (int parent = (myInfoHeap.studCnt - 1) / 2; parent >= 0; parent--) {
        // Find  the biggest child
        int LC = (parent * 2) + 1;
        int RC = (parent * 2) + 2;
        int child = getBigChild(myInfoHeap, parent);
        while (strcmp(myInfoHeap.data[child].ID, myInfoHeap.data[parent].ID) > 0 && child < myInfoHeap.studCnt) {
            swapStud(&myInfoHeap.data[child], &myInfoHeap.data[parent]);
            parent = child;
            child = getBigChild(myInfoHeap, parent);
        }
    }

    return myInfoHeap;
}