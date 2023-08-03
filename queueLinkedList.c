#include <stdio.h>
#include <stdlib.h>

typedef char String[30];

typedef struct {
    char name[30];
    int age;
    int id;
    int year;
    char program[10];
} studentDetails;

typedef struct node {
    studentDetails data;
    struct node *next;
} *nodePtr, node;

typedef struct {
    nodePtr front;
    nodePtr tail;
} Queue, *QueuePtr;

void initQueue(QueuePtr *q) {
    (*q)->front = NULL;
    (*q)->tail = NULL;
}

void createStudent(studentDetails *s) {
    printf("Enter name: ");
    fflush(stdin);
    gets(s->name);
    printf("Enter age: ");
    scanf("%d", &s->age);
    printf("Enter ID: ");
    scanf("%d", &s->id);
    printf("Enter year: ");
    scanf("%d", &s->year);
    printf("Enter program: ");
    fflush(stdin);
    gets(s->program);
}

void enqueue(QueuePtr *q, studentDetails s) {
    nodePtr newNode = malloc(sizeof(node));
    newNode->data = s;
    newNode->next = NULL;

    if ((*q)->front == NULL) {
        (*q)->front = (*q)->tail = newNode;
    } else {
        (*q)->tail->next = newNode;
        (*q)->tail = (*q)->tail->next;
    }
}

void dequeue(QueuePtr *q) {
    nodePtr delete;
    delete = (*q)->front;
    (*q)->front = (*q)->front->next;
    free(delete);
}

void visualize(QueuePtr q) {
    nodePtr trav = q->front;
    printf("%5s | %15s | %15s | %15s | %s\n", "NAME", "AGE", "ID", "YEAR", "PROGRAM");
    while (trav != NULL) {
        printf("%5s | %15d | %15d | %15d | %s\n", trav->data.name, trav->data.age, trav->data.id, trav->data.year, trav->data.program);
        trav = trav->next;
    }
}

int main() {
    QueuePtr myQueue;
    initQueue(&myQueue);
    
    String menu[3] = {"Enqueue", "Dequeue", "Visualize"};
    int input;

    do {
        printf("Choose from the following >0 to exit\n");
        for (int i = 0; i < 3; i++) {
            printf("%d. %s\n", i+1, menu[i]);
        }
        scanf("%d", &input);
        system("cls");

        switch (input) {
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

    } while (input != 0);
    printf("Exit\n");

    return 0;
}