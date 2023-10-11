#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    int front;
    int rear;
} Queue;

// function prototypes
void initQueue(Queue *Q);
void enqueue(Queue *Q, Studrec *student);
void dequeue(Queue *Q);
void addStudent(Studrec *student);
float computeAverage(GPA studGrade);
GPA initializeGrades();
void addStudentGrade(Studrec *student);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void traverse(Queue *Q);
void displayGrades(Studrec student);

int main() {
    Queue myQueue;
    initQueue(&myQueue);
    printf("%s", myQueue.data[0].name);
    Studrec stud1;
    enqueue(&myQueue, &stud1);
    Studrec stud2;
    enqueue(&myQueue, &stud2);
    Studrec stud3;
    enqueue(&myQueue, &stud3);
    Studrec stud4;
    enqueue(&myQueue, &stud4);
    traverse(&myQueue);
    displayGrades(stud1);

    return 0;
}

void initQueue(Queue *Q) {
    int i;
    Q->front = 6;
    Q->rear = Q->front - 1;

    for (i = 0; i < MAX; i++) {
        Q->data[i] = (Studrec){"XXXX", "XXXX", NULL};
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

void addStudentGrade(Studrec *student) {
    student->grades = initializeGrades();
    int choice;
    printf("Add a grade? 1 to add 0 to exit\n");
    scanf("%d", &choice);
    while (choice != 0) {
        student->grades = realloc(student->grades, (student->grades->count + 1) * sizeof(struct grades));
        printf("Input grade: ");
        scanf("%f", &student->grades[student->grades->count].grade);
        
        student->grades->count++;

        printf("Add more... ? press 1\n");
        scanf("%d", &choice);
    }
}

float computeAverage(GPA studGrade) {
    int i;
    float total = 0, average = 0;
    for (i = 0; i < studGrade->count; i++) {
        total += studGrade[i].grade;
    }

    return (average = total / studGrade->count);
}

bool isEmpty(Queue Q) {
    return (Q.front == (Q.rear + 1 % MAX)) ? 1 : 0; 
}

bool isFull(Queue Q) {
    return ((Q.rear + 2) % MAX == Q.front) ? 1 : 0;
}

void addStudent(Studrec *student) {
    printf("Enter name: ");
    fflush(stdin);
    gets(student->name);
    printf("Enter course: ");
    fflush(stdin);
    gets(student->course);

    addStudentGrade(student);
}

void enqueue(Queue *Q, Studrec *student) {
    if (isFull(*Q)) {
        printf("Circular array is full cannot enqueue\n");  
    } else {
        addStudent(student);
        Q->rear = (Q->rear + 1) % MAX;
        Q->data[Q->rear] = *student;
    }
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q)) {
        printf("Circular Array is empty cannot dequeue\n");
    } else {
        Q->front = (Q->front + 1) % MAX;
    }
}

void traverse(Queue *Q) {
    printf("STUDENT LIST\n");
    int temp = Q->front;
    printf("Student name[%d]: %s\n",temp, Q->data[temp].name);
    Q->rear = Q->front;
    dequeue(Q);
    while (temp != Q->front && strcmp(Q->data[Q->front].name, "XXXX") != 0) {
        printf("Student[%d] name: %s\n",Q->front, Q->data[Q->front].name);
        Q->rear = Q->front;
        dequeue(Q);
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




