#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 5

typedef char String[30];

typedef struct {
    char name[50];
    int age;
    int id;
    int year;
    char program[10];
} studentDetails;

typedef struct {
    studentDetails student[MAX];
    int top;
} Stack;

void initStack(Stack *list) {
    list->top = -1;
}

void createStudent(studentDetails *s) {
    printf("Enter name: ");
    fflush(stdin);
    gets(s->name);
    printf("Enter age: ");
    scanf("%d", &s->age);
    printf("Enter id: ");
    scanf("%d", &s->id);
    printf("Enter year: ");
    scanf("%d", &s->year);
    printf("Enter program: ");
    fflush(stdin);
    gets(s->program);

}

bool isEmpty(Stack s) {
    return (s.top == -1) ? 1 : 0;
}

void push(Stack *list, studentDetails studentInfo) {
    if (isEmpty(*list)) {
        list->top++;
    }

    list->student[list->top++] = studentInfo;
}

void pop(Stack *list) {
    if (!(isEmpty(*list))) {
        list->top--;
    }
}

studentDetails peek(Stack list) {
    return list.student[list.top - 1];
}

void visualizeStack(Stack list) {
    if (isEmpty(list)) {
        return;
    }

    for (int i = 0; i < list.top; i++) {
        printf("%5s | %15d | %15d | %15d | %s\n", list.student[i].name, list.student[i].age, list.student[i].id, list.student[i].year, list.student[i].program);
    }
}

int main() {
    Stack s;
    initStack(&s);

    String menu[3] = {"Push student", "Pop student", "Visualize Stack"};
    int input;
    printf("Choose from the following:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i+1, menu[i]);
    }
    do {
        scanf("%d", &input);

        switch(input) {
            case 1:
                studentDetails student;
                createStudent(&student);
                push(&s, student);
                break;
            
            case 2: 
                pop(&s);
                break;
            
            case 3:
                visualizeStack(s);
        }


    } while (input != 0);
    
    return 0;
}