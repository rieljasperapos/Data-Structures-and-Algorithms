#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef enum {
    ASIAN, EU_US
} makeType;

typedef enum {
    FALSE, TRUE
} Boolean;

typedef struct {
    char brand[20];
    char model[20];
    int year;
    makeType carMake;
} CarType;

typedef struct {
    CarType car[MAX];
    int top;
} Stack;

typedef struct {
    CarType car[MAX];
    int front;
    int rear;
} Queue;

typedef struct {
    Stack S;
    Queue Q;
} ComboSQ;

// Stack
void initStack(Stack *S);
void push(CarType c, Stack *S);
CarType pop(Stack *S);
Boolean isEmptyStack(Stack S);
Boolean isFullStack(Stack S);

// Queue
void initQueue(Queue *Q);
void enqueue(CarType c, Queue *Q);
CarType dequeue(Queue *Q);
Boolean isEmptyQueue(Queue Q);
Boolean isFullQueue(Queue Q);

Boolean searchCarModel(ComboSQ SQ, CarType car);

int main() {
    ComboSQ SQ;

    // Stack
    initStack(&SQ.S);

    // Cars in stack (asian cars)
    CarType myStackCar = {"Toyota", "Wigo", 2019, ASIAN};
    CarType myStackCar1 = {"Toyota", "Avanza", 2019, ASIAN};
    CarType myStackCar2 = {"Toyota", "Raize", 2019, ASIAN};
    CarType myStackCar3 = {"Toyota", "86", 2022, ASIAN};

    push(myStackCar, &SQ.S);
    push(myStackCar1, &SQ.S);
    push(myStackCar2, &SQ.S);
    push(myStackCar3, &SQ.S);

    // CarType poppedStackCar = pop(&SQ.S);
    // printf("Pop: %s %d\n", poppedStackCar.model, poppedStackCar.year);

    // Queue
    initQueue(&SQ.Q);

    //Cars in queue (non asian cars)
    CarType myQueueCar = {"Porsche", "718 Cayman", 2024, EU_US};
    CarType myQueueCar1 = {"BMW", "M3 Sedan", 2021, EU_US};
    CarType myQueueCar2 = {"Porsche", "718 Boxster", 2020, EU_US};
    CarType myQueueCar3 = {"Porsche", "911 Carrera", 2019, EU_US};

    enqueue(myQueueCar, &SQ.Q);
    enqueue(myQueueCar1, &SQ.Q);
    enqueue(myQueueCar2, &SQ.Q);
    enqueue(myQueueCar3, &SQ.Q);

    // CarType dequeueCar = dequeue(&SQ.Q);

    CarType carToSearch = {"Hyundai", "718 Boxster", 2019, EU_US};
    Boolean found = searchCarModel(SQ, carToSearch);
    (found) ? printf("CAR FOUND") : printf("CAR NOT FOUND");

    return 0;
}

// Stack
void initStack(Stack *S) {
    S->top = -1;
}

Boolean isEmptyStack(Stack S) {
    return (S.top == -1) ? TRUE : FALSE;
}

Boolean isFullStack(Stack S) {
    return ((S.top + 1) == MAX) ? TRUE : FALSE;
}

void push(CarType c, Stack *S) {
    // isFullStack(*S) ? (S->car[++S->top] = c) : printf("STACK IS EMPTY");
    if (!(isFullStack(*S))) {
        S->car[++S->top] = c;
    } else {
        printf("CANNOT PUSH STACK IS ALREADY FULL\n");
    }
}

CarType pop(Stack *S) {
    CarType temp;
    if (!(isEmptyStack(*S))) {
        temp = S->car[S->top];
        S->top--;
    } else {
        temp.year = -1;
        printf("CANNOT POP STACK IS ALREADY EMPTY\n");
    }

    return temp;
}

// Queue (circular)
void initQueue(Queue *Q) {
    Q->front = 4;
    Q->rear = 3;

    int indx;
    for (indx = 0; indx < MAX; indx++) {
        strcpy(Q->car[indx].model, "XXXX");
    }
}

Boolean isEmptyQueue(Queue Q) {
    return (Q.front == (Q.rear + 1) % MAX) ? TRUE : FALSE;
}

Boolean isFullQueue(Queue Q) {
    return (Q.front == (Q.rear + 2) % MAX) ? TRUE : FALSE;
}

void enqueue(CarType c, Queue *Q) {
    if (!(isFullQueue(*Q))) {
        Q->rear = (Q->rear + 1) % MAX;
        Q->car[Q->rear] = c;
    } else {
        printf("CANNOT ENQUEUE QUEUE IS ALREADY FULL\n");
    }
}

CarType dequeue(Queue *Q) {
    CarType temp;
    if (!(isEmptyQueue(*Q))) {
        temp = Q->car[Q->front];
        Q->front = (Q->front + 1) % MAX;
    }  else {
        temp.year = -1;
        printf("CANNOT DEQUEUE QUEUE IS ALREADY EMPTY\n");
    }

    return temp;
}

Boolean searchCarModel(ComboSQ SQ, CarType car) {
    Boolean found = FALSE;
    CarType carQueue;
    printf("Car to search: %s\n", car.model);
    
    if (car.carMake == ASIAN) {
        while (!(isEmptyStack(SQ.S))) {
            printf("Car Stack[%d]: %s\n", SQ.S.top, SQ.S.car[SQ.S.top].model);
            if (strcmp(car.model, SQ.S.car[SQ.S.top].model) == 0) {
                found = TRUE;
            }
            SQ.S.top--;
        }
    } else {
        int temp = SQ.Q.front;
        carQueue = dequeue(&SQ.Q);
        if (carQueue.year != -1) {
            while(temp != SQ.Q.front && strcmp(carQueue.model, "XXXX") != 0) {
                SQ.Q.rear = SQ.Q.front;
                if (strcmp(car.model, carQueue.model) == 0) {
                    found = TRUE;
                }
                printf("Car Queue: %s\n", carQueue.model);
                carQueue = dequeue(&SQ.Q);
            }
        } else {
            printf("Cannot search, queue is empty\n");
        }
    }

    return found;
    
}


