#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

// Structure definition

typedef struct grades {
    float grade;
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
void addStudent(LIST *L, Studrec *student);
GPA initializeGrades();
void addStudentGrade(Studrec *student);
float getAverage(Studrec student);
void displayGrades(Studrec student);
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
    addStudent(&myList, &stud1);

    Studrec stud2;
    addStudent(&myList, &stud2);

    displayList(myList);
    displayGrades(stud2);

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

void addStudentGrade(Studrec *student) {
    student->grades = initializeGrades();
    int choice;
    printf("Add a grade? 1: Yes 0: NO\n");
    scanf("%d", &choice);
    while(choice != 0) {
        student->grades = realloc(student->grades, (student->grades->count + 1) * sizeof(struct grades));
        printf("Input student grade: ");
        scanf("%f", &student->grades[student->grades->count].grade);

        student->grades->count++;

        printf("Add more... ? press 1\n");
        scanf("%d", &choice);
    }
}

float getAverage(Studrec student) {
    int i;
    float average = 0;
    float total = 0;
    for (i = 0; i < student.grades->count; i++) {
        total += student.grades[i].grade;
    }
    average = total / student.grades->count;

    return average;

}

void addStudent(LIST *L, Studrec *student) {
    printf("Enter name: ");
    fflush(stdin);
    gets(student->name);

    printf("Enter course: ");
    fflush(stdin);
    gets(student->course);

    addStudentGrade(student);

    L->data[L->count++] = *student;
}

void displayGrades(Studrec student) {
    int i,j;

    printf("%s's Grades\n", student.name);
    for (i= 0; i < student.grades->count; i++) {
        printf("Grade[%d]: %.2f\n",i, student.grades[i].grade);
    }

    float average = 0;
    average = getAverage(student);
    printf("GPA: %.2f\n", average);
}

void displayList(LIST L) {
    int i;
    printf("STUDENT RECORD\n\n");
    printf("%s %30s %15s\n", "NO.", "NAME", "COURSE");
    for (i = 0; i < MAX; i++) {
        printf("%3d %30s %15s\n",i, L.data[i].name, L.data[i].course);
        printf("-------------------------------------------------\n");
    }
}
