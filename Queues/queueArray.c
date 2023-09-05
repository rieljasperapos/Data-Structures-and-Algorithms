#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 5
#define EMPTY -1

typedef char String[30];

typedef struct {
    char name[30];
    int age;
    int id;
    int year;
    char program[10];
} studentDetails;

typedef struct {
    studentDetails data[MAX];
    int front;
    int tail;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->tail = -1;
}

bool isEmpty(Queue q) {
    return (q.tail + 1 == q.front) ? 1 : 0;
}

bool isFull(Queue q) {
    return (q.tail == MAX) ? 1 : 0;
}

void enqueue(Queue *q, studentDetails s) {
    if (isFull(*q)) {
        printf("Queue is full\n");
        return;
    }

    q->tail = q->tail + 1;

    printf("TAIL VALUE: %d\n", q->tail);
    q->data[q->tail] = s;
}

void dequeue(Queue *q) {
    if (isEmpty(*q)) {
        printf("Queue is empty, cannot dequeue\n");
        return;
    }

    q->data[q->front].id = EMPTY;
    q->front = q->front + 1;
}

void visualize(Queue q) {
    printf("%5s | %10s | %10s | %10s | %10s | %s\n", "INDEX", "NAME", "AGE", "ID", "YEAR", "PROGRAM");
    for (int i = 0; i <= q.tail; i++) {
        printf("%5d | ", i);
        if (q.data[i].id != EMPTY) {
            printf("%10s | %10d | %10d | %10d | %s\n", q.data[i].name, q.data[i].age, q.data[i].id, q.data[i].year, q.data[i].program);
        } else {
            printf("%10s | %10s | %10s | %10s | %s\n", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY");
        }
    }
}

void createStudent(studentDetails *student) {
    printf("Enter name: ");
    fflush(stdin);
    gets(student->name);
    printf("Enter age: ");
    scanf("%d", &student->age);
    printf("Enter ID: ");
    scanf("%d", &student->id);
    printf("Enter year: ");
    scanf("%d", &student->year);
    printf("Enter Program: ");
    fflush(stdin);
    gets(student->program);
}

int main() {
    Queue myQueue;
    initQueue(&myQueue);

    printf("Choose from the following >0 to exit\n");
    String menu[3] = {"Enqueue", "Dequeue", "Visualize"};
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    int input;
    do {
        scanf("%d", &input);

        switch(input) {
            case 1:
                studentDetails student;
                createStudent(&student);
                enqueue(&myQueue, student);
                printf("Enqueue\n");
                break;
            
            case 2:
                dequeue(&myQueue);
                printf("Dequeue\n");
                break;
            
            case 3:
                visualize(myQueue);
                printf("Visualize\n");
                break;
        }
    } while(input != 0);
    printf("Exit\n");
    
    return 0;
}