#include <stdio.h>
#include <stdlib.h>

typedef char String[30];

typedef struct {
    char name[50];
    int age;
    int id;
    int year;
    char program[10];
} studentDetails;

typedef struct node{
    studentDetails data;
    struct node *next;
} Stack, *stackPtr;

void initList(stackPtr *list) {
    *list = NULL;
}

void push(stackPtr *list, studentDetails s) {
    stackPtr newNode = malloc(sizeof(Stack));
    newNode->data = s;
    newNode->next = *list;
    *list = newNode;
}

void pop(stackPtr *list) {
    stackPtr delete;
    delete = *list;
    *list = (*list)->next;
    free(delete);
}

void visualize(stackPtr list) {
    while (list != NULL) {
        printf("%5s | %15d | %15d | %15d | %s\n", list->data.name, list->data.age, list->data.id, list->data.year, list->data.program);
        list = list->next;
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
    stackPtr top;
    initList(&top);

    int input;
    String menu[3] = {"Push student", "Pop student", "Visualize stack"};

    printf("Choose from the following >0 to exit from the menu: \n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i+1, menu[i]);
    }

    do {
        scanf("%d", &input);

        switch (input) {
            case 1:
                studentDetails s;
                createStudent(&s);
                push(&top, s);
                break;
            
            case 2:
                if (top == NULL) {
                    printf("List is empty\n");
                } else {
                    printf("POPPED %s\n", top->data.name);
                }
                pop(&top);
                break;

            case 3:
                visualize(top);
                break;
        }

    } while (input != 0);
    printf("Menu exit\n");





}
