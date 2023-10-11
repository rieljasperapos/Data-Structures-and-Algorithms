#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char elem[MAX];
    int front;
    int rear;
} Queue;

void initialize(Queue *Q);
void enqueue(Queue *Q, char elem);
void dequeue(Queue *Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void traverse(Queue *Q);

int main() {
    Queue myQueue;
    initialize(&myQueue);
    enqueue(&myQueue, 'G');
    enqueue(&myQueue, 'D');
    enqueue(&myQueue, 'S');
    enqueue(&myQueue, 'C');
    enqueue(&myQueue, '-');
    enqueue(&myQueue, 'U');
    enqueue(&myQueue, 'S');
    enqueue(&myQueue, 'C');
    enqueue(&myQueue, 'C');
    enqueue(&myQueue, 'C');
    enqueue(&myQueue, 'C');
    

    
    traverse(&myQueue);
    
    return 0;
}

void initialize(Queue *Q) {
    Q->front = 9;
    Q->rear = 8;

    int i;
    for (i = 0; i < MAX; i++) {
        Q->elem[i] = 'X';
    }
}

bool isEmpty(Queue Q) {
    return (Q.front == (Q.rear +1) % MAX) ? 1 : 0;
}

bool isFull(Queue Q) {
    return ((Q.rear + 2) % MAX == Q.front) ? 1 : 0;
}

void enqueue(Queue *Q, char data) {
    if (isFull(*Q)) {
        printf("ARRAY IS FULL\n");
    } else {
        Q->rear = (Q->rear + 1) % MAX;
        Q->elem[Q->rear] = data;
    }
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q)) {
        printf("ARRAY IS NOW EMPTY CANNOT DEQUEUE\n");
    }
    Q->front = (Q->front + 1) % MAX;
}

void traverse(Queue *Q) {
    int temp = Q->front;
    Q->rear = Q->front;
    printf("%c ", Q->elem[temp]);
    dequeue(Q);
    while (temp != Q->front && Q->elem[Q->front] != 'X') {
        Q->rear = Q->front;
        printf("%c ", Q->elem[Q->front]);
        dequeue(Q);
    }
}