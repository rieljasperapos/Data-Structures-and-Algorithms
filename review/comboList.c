#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// structure definition
typedef struct {
  char FN[24], LN[16], MI;
} nameType;

typedef struct  {
  char ID[10];
  nameType name;
  char course[8];
  int yrLevel;
} studRec;

typedef struct node {
  studRec stud;
  struct node *link;
} *studLink;

typedef struct arr {
  studRec stud[MAX];
  int count;
} studArray;

typedef struct list {
  studLink IT;
  studArray CS;
} *ComboList;

void insertSorted(studLink *A, studRec s);
studRec newStud(char *ID, nameType name, char *course, int yrLevel);
nameType newName(char *FN, char *LN, char MI);
void displayList(studLink L);
ComboList createComboList(studLink *A);
void displayComboList(ComboList L);

int main() {
  studLink sortedLink = NULL;
  studRec myStud = newStud("22105020", newName("Riel", "Apos", 'A'), "BSCS", 2);
  studRec myStud1 = newStud("12345678", newName("Aqua", "Hoshino", 'A'), "BSIT", 2);
  studRec myStud2 = newStud("11125678", newName("Ruby", "Hoshino", 'A'), "BSIT", 2);
  studRec myStud3 = newStud("10025678", newName("Kana", "Arima", 'A'), "BSIS", 2);
  studRec myStud4 = newStud("10125678", newName("Gojo", "Satoru", 'A'), "BSCS", 2);
  insertSorted(&sortedLink, myStud);
  insertSorted(&sortedLink, myStud1);
  insertSorted(&sortedLink, myStud2);
  insertSorted(&sortedLink, myStud3);
  insertSorted(&sortedLink, myStud4);

  ComboList myList = createComboList(&sortedLink);
  displayComboList(myList);

  return 0;
}

nameType newName(char *FN, char *LN, char MI) {
  nameType temp;
  strcpy(temp.FN, FN);
  strcpy(temp.LN, LN);
  temp.MI = MI;

  return temp;
}

studRec newStud(char *ID, nameType name, char *course, int yrLevel) {
  studRec temp;
  strcpy(temp.ID, ID);
  temp.name = name;
  strcpy(temp.course, course);
  temp.yrLevel = yrLevel;

  return temp;
}

void insertSorted(studLink *A, studRec s) {
  studLink *trav;
  for (trav = A; *trav != NULL && strcmp((*trav)->stud.ID, s.ID) < 0; trav = &(*trav)->link) {}
  studLink temp = (studLink)malloc(sizeof(struct node));
  if (temp != NULL) {
    temp->stud = s;
    temp->link = *trav;
    *trav = temp;
  }
}

ComboList createComboList(studLink *A) {
  ComboList temp = (ComboList)malloc(sizeof(struct list));
  studLink *trav;
  if (temp != NULL) {
    temp->IT = NULL;
    temp->CS.count = 0;
    for (trav = A; *trav != NULL;) {
      if (strcmp((*trav)->stud.course, "BSCS") == 0) {
        temp->CS.stud[temp->CS.count++] = (*trav)->stud;
        *trav = (*trav)->link;
      } else if (strcmp((*trav)->stud.course, "BSIS") == 0) {
        studLink temp = *trav;
        *trav = (*trav)->link;
        free(temp);
      } else {
        trav = &(*trav)->link;
      }
    }
    temp->IT = *A;
  }
  return temp;
}

void displayList(studLink L) {
  while (L != NULL) {
    printf("%s ", L->stud.ID);
    L = L->link;
  }
}

void displayComboList(ComboList L) {
  printf("\nBSCS\n");
  int indx;
  for (indx = 0; indx < L->CS.count; indx++) {
    printf("%s: %s\n", L->CS.stud[indx].course, L->CS.stud[indx].name.FN);
  }

  printf("\nBSIT\n");
  while (L->IT != NULL) {
    printf("%s: %s\n", L->IT->stud.course, L->IT->stud.name.FN);
    L->IT = L->IT->link;
  }
}