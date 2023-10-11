#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

// data structure definition

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
    int top;
} Stack;

// function prototypes

void initStack(Stack *S);
GPA initializeGrades();
void addStudentGrade(Studrec *student);
float computeAverage(GPA studGrade);
void push(Stack *S, Studrec *student);
void pop(Stack *S);
Studrec peek(Stack S);
bool isEmpty(Stack S);
bool isFull(Stack S);
void displayStack(Stack S);
void displayGrades(Studrec student);

int main() {
    Stack myStack;
    initStack(&myStack);
    Studrec stud1;
    push(&myStack, &stud1);

    Studrec stud2;
    push(&myStack, &stud2);

    Studrec stud3;
    push(&myStack, &stud3);

    Studrec stud4;
    push(&myStack, &stud4);

    Studrec stud5;
    push(&myStack, &stud5);

    pop(&myStack);
    pop(&myStack);

    displayStack(myStack);


    displayGrades(stud1);
    displayGrades(stud2);

    Studrec studPeek = peek(myStack);
    printf("Peek: %s\n", studPeek.name);
    
    return 0;
}

void initStack(Stack *S) {
    S->top = -1;
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

float computeAverage(GPA studGrade) {
    int i, total = 0;
    float average;
    for (i = 0; i < studGrade->count; i++) {
        total += studGrade[i].grade;
    }

    return (average = total / studGrade->count);
}

bool isEmpty(Stack S) {
    return (S.top == -1) ? 1 : 0;
}

bool isFull(Stack S) {
    return (S.top == MAX) ? 1 : 0;
}

void push(Stack *S, Studrec *student) {
    if (isFull(*S)) {
        printf("Stack is full cannot push anymore\n");
    } else {
        printf("Enter name: ");
        fflush(stdin);
        gets(student->name);
        printf("Enter Course: ");
        fflush(stdin);
        gets(student->course);

        addStudentGrade(student);

        S->data[++S->top] = *student;
    }
}

void pop(Stack *S) {
    if (isEmpty(*S)) {
        printf("Cannot pop Stack is empty\n");
    } else {
        S->top--;
    }
}

Studrec peek(Stack S) {
    return S.data[S.top];
}

void displayStack(Stack S) {
    int i;
    printf("STUDENT RECORD\n\n");
    printf("%s\n", S.data[0].name);
    printf("%s %30s %15s\n", "NO.", "NAME", "COURSE");
    for (i = S.top ; i != -1 && i < MAX; i--) {
        printf("%3d %30s %15s\n",i, S.data[i].name, S.data[i].course);
        printf("-------------------------------------------------\n");
    }
}

void displayGrades(Studrec student) {
    int i;
    printf("%s's Grades\n", student.name);
    for (i = 0; i < student.grades->count; i++) {
        printf("Grades[%d]: %.2f\n", i, student.grades[i].grade);
    }

    printf("GPA: %.2f\n", computeAverage(student.grades));
}
