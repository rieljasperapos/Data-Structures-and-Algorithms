#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

// Structure definition

typedef struct grades {
    float grades;
    float average;
    int count;
} *GPA;

typedef struct {
    char name[50];
    char course[8];
    GPA grades;
} Studrec;

typedef struct {
    Studrec data[MAX];
    int count;
} LIST;

// function prototypes

void initializeList(LIST *L);
void addStudent(LIST *L, Studrec student);
GPA initializeGrades();
GPA addStudentGrade(LIST *L);
void displayGrades(GPA grades);
void displayList(LIST L);
Studrec createStud(char *name, char *course, GPA grades);

int main() {
    // TO DO:
    // Add a student to the ADT List
    // addStudent()
    // Display the student records including also the students grade
    // implement the myGrade below in the Student Records
    LIST myList;
    initializeList(&myList);
    displayList(myList);

    Studrec stud1;
    addStudent(&myList, stud1);

    Studrec stud2;
    addStudent(&myList, stud2);

    displayList(myList);

    return 0;
}

Studrec createStud(char *name, char *course, GPA grades) {
    Studrec s;
    strcpy(s.name, name);
    strcpy(s.course, course);

    s.grades = grades;

    return s;
}

void initializeList(LIST *L) {
    int i;
    for (i = 0; i < MAX; i++) {
        GPA studGrade = initializeGrades();
        L->data[i] = createStud("EMPTY", "EMPTY", studGrade);
    }
    L->count = 0;
}

GPA initializeGrades() {
    GPA studGrades;
    studGrades = malloc(sizeof(struct grades));
    if (studGrades != NULL) {
        studGrades->count = 0;
    }

    return studGrades;
}

GPA addStudentGrade(LIST *L) {
    L->data[L->count].grades = initializeGrades();
    int choice;
    printf("Add a grade? 1: Yes 0: NO\n");
    scanf("%d", &choice);
    while(choice != 0) {
        L->data[L->count].grades = realloc(L->data[L->count].grades, (L->data[L->count].grades->count + 1) * sizeof(struct grades));
        printf("Input student grade: ");
        scanf("%f", &L->data[L->count].grades[L->data[L->count].grades->count].grades);

        L->data[L->count].grades->count++;

        printf("Add more... ? press 1\n");
        scanf("%d", &choice);
    }

    return L->data[L->count].grades;
}

void addStudent(LIST *L, Studrec student) {
    printf("Enter name: ");
    fflush(stdin);
    gets(student.name);

    printf("Enter course: ");
    fflush(stdin);
    gets(student.course);

    student.grades = addStudentGrade(L);
    L->data[L->count++] = student;
}

void displayGrades(GPA myGrades) {
    int i;
    for (i = 0; i < myGrades->count ; i++) {
        printf("Grade[%d]: %.2f\n", i, (myGrades + i)->grades);
    }
}

void displayList(LIST L) {
    int i;
    printf("%s %30s %15s\n", "NO.", "NAME", "COURSE");
    for (i = 0; i < MAX; i++) {
        printf("%3d %30s %15s\n\n",i, L.data[i].name, L.data[i].course);
        if (L.data[i].grades->count == 0) {
            printf("\nNo grades inputted\n");
        } else {
            int indx;
            for (indx = 0; indx < L.data[i].grades->count; indx++) {
                printf("Grades[%d]: %.2f\n", indx, L.data[i].grades[indx].grades);
            }
        }
        printf("-------------------------------------------------\n");
    }
}
