#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

// Structure definition
typedef struct {
    char FN[24];
    char MI;
    char LN[16];
} Nametype;

typedef struct {
    Nametype name;
    int ID;
    char course[8];
    int yrLevel;
} Studtype;


// Function Prototypes
void displayStudent(Studtype s);
void displayHeader();
void writeFile();
void readFile();

int main() {
    Studtype students[MAX];
    students[0] = (Studtype){"Riel", 'A', "Apos", 22105020, "BSCS", 2};
    students[1] = (Studtype){"Jedro", 'A', "Morales", 22105020, "BSCS", 2};
    students[2] = (Studtype){"John", 'A', "Doe", 22105020, "BSCS", 2};
    students[3] = (Studtype){"Jay", 'A', "Ectarcio", 22105020, "BSCS", 2};
    students[4] = (Studtype){"Apple", 'D', "App", 22105020, "BSCS", 2};

    writeFile(students);
    readFile();

    return 0;
}

void writeFile(Studtype *students) {
    printf("IM WRITING: %s\n", students[0].name);
    FILE *fp = fopen("studentrec.txt", "wb");
    if (fp == NULL) {
        printf("Cannot write to a file\n");
    } else {
        fwrite(students, sizeof(Studtype), 5, fp);
    }

    fclose(fp);
}

void displayHeader() {
    printf("\n\n");
    printf("%-10s", "ID No.");
    printf("%-16s", "Lastname");
    printf("%-24s", "Firstname");
    printf("%-3s", "MI");
    printf("%-8s", "Course");
    printf("%5s", "Year");
    printf("\n");
    printf("%-10s", "======");
    printf("%-16s", "========");
    printf("%-24s", "=========");
    printf("%-3s", "==");
    printf("%-8s", "======");
    printf("%5s", "====");
}

void displayStudent(Studtype s) {
    printf("\n");
    printf("%-10d", s.ID);
    printf("%-16s", s.name.LN);
    printf("%-24s", s.name.FN);
    printf("%-3c", s.name.MI);
    printf("%-8s", s.course);
    printf("%5d", s.yrLevel);
    // printf("%-10s", "======");
    // printf("%-16s", "========");
    // printf("%-24s", "=========");
    // printf("%-3s", "==");
    // printf("%-8s", "======");
    // printf("%5s", "====");
}

void readFile() {
    FILE *fp;
    Studtype stud;
    int count = 0;
    char filename[50];

    // printf("Enter filename: ");
    // scanf("%s", filename);

    displayHeader();
    fp = fopen("studentrec.txt", "rb");
    if (fp == NULL) {
        printf("Cannot open file\n");
    } else {
        while(fread(&stud, sizeof(Studtype), 1, fp)) {
            displayStudent(stud);
            count++;
            if (count == 20) {
                printf("\n");
                system("pause");
            }
        }
    }

    fclose(fp);
}

