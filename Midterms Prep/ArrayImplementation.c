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
void addStudentGrade(GPA grades);
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




    // GPA myGrade = initializeGrades();
    // printf("myGrade is: %p\n", myGrade);
    // addStudentGrade(myGrade);
    // addStudentGrade(myGrade);
    // displayGrades(myGrade);
    // printf("My grades count is: %d\n", myGrade->count);

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
        GPA studGrade;
        L->data[i] = createStud("EMPTY", "EMPTY", initializeGrades(&studGrade));
    }
}

GPA initializeGrades() {
    GPA studGrades;
    studGrades = malloc(sizeof(struct grades));
    if (studGrades != NULL) {
        studGrades->count = 0;
    }

    return studGrades;
}

void addStudentGrade(GPA studGrades) {
    studGrades = realloc(studGrades, (studGrades->count + 1) * sizeof(struct grades));
    printf("Input student grade: ");
    scanf("%f", &studGrades[studGrades->count++].grades);
}

void displayGrades(GPA myGrades) {
    int i;
    for (i = 0; i < myGrades->count ; i++) {
        printf("Grade[%d]: %.2f\n", i, (myGrades + i)->grades);
    }
}

void displayList(LIST L) {
    int i;
    for (i = 0; i < MAX; i++) {
        printf("Student %d\n%s, %s\n",i, L.data[i].name, L.data[i].course);
        if (L.data[i].grades->count == 0) {
            printf("No grades inputted\n");
        } else {
            int indx;
            for (indx = 0; indx < L.data[i].grades->count; indx++) {
                printf("Grades[%d]: %.2f\n", indx, L.data[i].grades[i].grades);
            }
        }
    }
}
